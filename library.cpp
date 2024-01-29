#include "library.h"




//prints long_number given
void long_number::print_ln() {
    if (sign == -1) {
        std::cout << '-';
    }
    for(int i = 0; i < value.size() - precision; ++i) {
        std::cout << value[i];
    }
    if (precision > 0){
        std::cout << '.';
    }
    for(size_t i = value.size() - precision; i < value.size(); ++i) {
        std::cout << value[i];
    }
    std::cout << std::endl;
}

//Return long_number which is an absolute value of given long_number
[[nodiscard]] long_number long_number::abs() const {
    long_number ret;
    ret.value = value;
    ret.precision = precision;
    ret.sign = 1;
    return ret;
}

//Compares absolute values of two long_numbers including those with different precisions. Returns 1 if this is greater, -1 if other is greater, 0 otherwise.
int long_number::compare_abs(long_number x) {
    int res = 0;

    if (x.value.size() - x.precision > value.size() - precision) {
        res = -1;
    } else if (x.value.size() - x.precision < value.size() - precision) {
        res = 1;
    } else {

        for (int i = 0; i < std::min(x.value.size(), value.size()); ++i) {
            if ((x.value)[i] > value[i]) {
                res = -1;
                break;
            } else if ((x.value)[i] < value[i]) {
                res = 1;
                break;
            }
        }

        if (res == 0 && x.precision > precision){
            int all_zeroes = 1;
            for (size_t i = std::min(x.value.size(), value.size()); i < x.value.size(); ++i) {
                if (x.value[i] != '0'){
                    all_zeroes = 0;
                    break;
                }
            }
            if (all_zeroes == 0) {
                res = -1;
            }
        } else if (res == 0 && x.precision < precision) {
            int all_zeroes = 1;
            for (size_t i = std::min(x.value.size(), value.size()); i < value.size(); ++i) {
                if (value[i] != '0'){
                    all_zeroes = 0;
                    break;
                }
            }
            if (all_zeroes == 0) {
                res = 1;
            }
        }
    }
    return res;
}

bool long_number::operator==(const long_number &x) {
    if (sign == x.sign && compare_abs(x) == 0) {
        return true;
    } else {
        return false;
    }
}

bool long_number::operator!=(const long_number& x) {
    if (sign != x.sign || compare_abs(x) != 0) {
        return true;
    } else {
        return false;
    }
}

//returns true if this is greater than given, otherwise - false
bool long_number::operator>(const long_number& x) {
    bool res = false;
    if (sign == x.sign && sign == 1) {
        res =  (compare_abs(x) == 1);
    }else if (sign == x.sign && sign == -1) {
        res = (compare_abs(x) == -1);
    }else if (sign == 1 && x.sign == -1) {
        if (value == "0" && x.value == "0") {
            res = false;
        } else {
            res = true;
        }
    } else if (sign == -1 && x.sign == 1)    {
        res = false;
    }
    return res;
}

//returns true if this is less than given, otherwise - false
bool long_number::operator<(const long_number& x) {
    bool res;
    if (this <= &x && *this != x){
        res = true;
    } else {
        res = false;
    }
    return res;
}

//returns true if this is less or equal to given, otherwise - false
bool long_number::operator<=(const long_number& x) {
    bool res;
    if (!(*this > x)) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

//returns true if this is greater or equal to given, otherwise - false
bool long_number::operator>=(const long_number& x) {
    bool res;
    if (this >= &x) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

//promotes precision of this long_number to precision of given long_number by adding 0s to the end
long_number long_number::promote_precision(const long_number& x){
    long_number ret;
    if (precision < x.precision) {
        ret.value = value;
        for(int i = 0; i < x.precision - precision; ++i){
            ret.value.push_back('0');
        }
        ret.precision = x.precision;
        ret.sign = sign;
        return ret;
    } else {
        return (*this);
    }

}

long_number long_number::sum_abs(long_number x) {
    long_number ret;
    long_number this_c = (*this).promote_precision(x);
    long_number x_c = x.promote_precision(*this);

    int u = 0;
    std::string a = this_c.value;
    std::string b = x_c.value;
    std::string ans;
    while(!a.empty() || !b.empty()){
        int z = !a.empty() ? (a.back() - '0') : 0;
        int y =  !b.empty() ? (b.back() - '0') : 0;
        ans += (std::to_string((z + y + u) % 10));
        u = (z + y + u) / 10;
        if (!a.empty()){
            a.pop_back();
        }
        if (!b.empty()){
            b.pop_back();
        }
    }
    if(u == 1){
        ans.push_back('1');
    }
    reverse(ans.begin(), ans.end());

    ret.value = ans;
    ret.sign = 1;
    ret.precision = x_c.precision;
    return ret;
}

long_number long_number::diff_abs(long_number x) {
    long_number ret;
    long_number this_c = (*this).promote_precision(x);
    long_number x_c = x.promote_precision(*this);

    int u = 0;
    std::string a = this_c.value;
    std::string b = x_c.value;
    std::string ans;
    while(!a.empty() || !b.empty()){
        int z = !a.empty() ? (a.back() - '0') : 0;
        int y = !b.empty() ? (b.back() - '0') : 0;
        if (z - y - u >= 0) {
            ans += (std::to_string((z - y - u) % 10));
            u = 0;
        } else {
            ans += (std::to_string((10 + z - y - u) % 10));
            u = 1;
        }
        if (!a.empty()){
            a.pop_back();
        }
        if (!b.empty()){
            b.pop_back();
        }
    }

    while (!ans.empty() && ans.back() == '0') {
        ans.pop_back();
    }

    reverse(ans.begin(), ans.end());


    ret.value = ans;
    ret.sign = 1;
    ret.precision = x_c.precision;
    return ret;
}

long_number long_number::operator-() const {
    long_number ret;
    ret.value = value;
    ret.precision = precision;
    ret.sign = -sign;
    return ret;
}

long_number long_number::operator+(long_number y) {
    long_number ret;
    if (sign == y.sign) {
        long_number sum = sum_abs(y);
        ret.value = sum.value;
        ret.precision = sum.precision;
        ret.sign = sign;
    } else {
        if (sign == -1) {
            if ((*this).abs() > y.abs()) {
                ret.sign = -1;
            } else {
                ret.sign = 1;
            }
        } else {
            if ((*this).abs() > y.abs()) {
                ret.sign = 1;
            } else {
                ret.sign = -1;
            }
        }
        if ((*this).abs() > y.abs()) {
            long_number diff = diff_abs(y);
            ret.value = diff.value;
            ret.precision = diff.precision;
        } else {
            long_number diff = y.diff_abs(*this);
            ret.value = diff.value;
            ret.precision = diff.precision;
        }
    }
    if (ret.value.empty()) {
        ret.value = "0";
    }
    return ret;
}

long_number long_number::operator-(const long_number& y) {
    long_number ret;
    long_number sum = (*this) + (-y);
    if (sum.value.empty()) {
        ret.value = "0";
    } else {
        ret.value = sum.value;
    }
    ret.precision = sum.precision;
    ret.sign = sum.sign;
    return ret;
}

std::string long_number::ln_to_string() {
    std::string ret;
    if (sign == -1) {
        ret.push_back('-');
    }
    for(int i = 0; i < value.size() - precision; ++i) {
        ret.push_back(value[i]);
    }
    if (precision > 0){
        ret.push_back('.');
    }
    for(size_t i = value.size() - precision; i < value.size(); ++i) {
        ret.push_back(value[i]);
    }
    return ret;
}
