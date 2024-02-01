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
    if ((int)(x.value.size() - x.precision) > (int)(value.size() - precision)) {
        res = -1;
    } else if ((int)(x.value.size() - x.precision) < (int)(value.size() - precision)) {
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

//overloaded operator ==. returns 1 if this long_number equals long_number y, 0 otherwise
bool long_number::operator==(const long_number &x) {
    if (sign == x.sign && compare_abs(x) == 0) {
        return true;
    } else {
        return false;
    }
}

//overloaded operator !=. returns 1 if this long_number not equals long_number y, 0 otherwise
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
    if (1 == x.sign && sign == 1) {

        res = compare_abs(x) == 1;
    }else if (-1 == x.sign && sign == -1) {
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
    bool res = false;
    if (1 == x.sign && sign == 1) {
        res = compare_abs(x) == -1;
    }else if (-1 == x.sign && sign == -1) {
        res = (compare_abs(x) == 1);
    }else if (sign == 1 && x.sign == -1) {
        res = false;
    } else if (sign == -1 && x.sign == 1)    {
        if (value == "0" && x.value == "0") {
            res = false;
        } else {
            res = true;
        }
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

//returns long number that equals sum of absolute values of this long_number and long_number x
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

//returns long number that equals difference of absolute values of this long_number and long_number x
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

//overloaded operator -. returns long_number -this
long_number long_number::operator-() const {
    long_number ret;
    ret.value = value;
    ret.precision = precision;
    ret.sign = -sign;
    return ret;
}

//overloaded operator +. returns long_number this + y
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

//overloaded operator -. returns long_number this - y
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

//overloaded operator *. returns long_number this * y
long_number long_number::operator*(const long_number& y) {
    long_number prod = simple_mult((*this), y);
    return prod;
}

//returns long_number this as a string
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

//default constructor. creates long_number 0;
long_number::long_number() {
    value = "0";
    sign = 1;
    precision = 0;
}

//constructor from int. creates long_number that equals x;
long_number::long_number(int x) {
    std::string s = std::to_string(std::abs(x));
    sign = (x > 0 ? 1 : -1);
    precision = 0;
    value = s;
}

//constructor from double. creates long number that equals x;
long_number::long_number(long double x) {
    std::string s = std::to_string(x);
    int i = 0;
    bool flag_point = false;
    int after_point = 0;
    std::string ret;

    if (s[0] == '-') {
        sign = -1;
        i++;
    } else {
        sign = 1;
    }

    while (i < s.size()) {
        if (s[i] == '.') {
            flag_point = true;
        }

        if (isdigit(s[i])) {
            ret.push_back(s[i]);

            if (flag_point) {
                after_point++;
            }
        }
        i++;
    }

    precision = after_point;
    value = ret;
}

//constructor from string. creates long number that equals x;
long_number::long_number(std::string x) {
    std::string s = x;
    int i = 0;
    bool flag_point = false;
    int after_point = 0;
    std::string ret;

    if (s[0] == '-') {
        sign = -1;
        i++;
    } else {
        sign = 1;
    }

    while (i < s.size()) {
        if (s[i] == '.') {
            flag_point = true;
        }

        if (isdigit(s[i])) {
            ret.push_back(s[i]);

            if (flag_point) {
                after_point++;
            }
        }
        i++;
    }

    precision = after_point;
    value = ret;
}

//simple multiplication with complexity o(x^2). returns long_number = x * y
long_number simple_mult(const long_number& x, const long_number& y) {
    std::string a = x.value;
    std::string b = y.value;

    int u = -1;
    while (a[u + 1] == '0') {
        u++;
    }

    if (u != -1) {
        a = a.substr(u + 1, a.size() - u - 1);
    }

    u = -1;
    while (b[u + 1] == '0') {
        u++;
    }

    if (u != -1) {
        b = b.substr(u + 1, b.size() - u - 1);
    }

    if (a == "0" || b == "0") {
        long_number ret;
        ret.sign = 1;
        ret.precision = 0;
        ret.value = "0";
        return ret;
    } else {
        std::string c(a.size() + b.size(), '0');

        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());


        for (int i = 0; i < a.size(); ++i) {
            for (int j = 0, carry = 0; j < b.size() || carry > 0; ++j) {
                int cur = (c[i + j] - '0') + (a[i] - '0') * (j < b.size() ? b[j] - '0' : 0) + carry;
                c[i + j] = cur % 10 + '0';
                carry = cur / 10;
            }
        }

        while (c.size() > 1 && c.back() == '0') {
            c.pop_back();
        }

        reverse(c.begin(), c.end());

        long_number ret;
        ret.sign = x.sign * y.sign;
        ret.precision = x.precision + y.precision;
        ret.value = c;

        if (ret.precision >= ret.value.size()) {
            std::string add;
            for (int i = 0; i < (ret.precision - ret.value.size() + 1); ++i) {
                add.push_back('0');
            }
            ret.value = add + ret.value;
        }

        return ret;
    }
}

//returns long_numbers that is reverse of given long_number with given precision.
//complexity is o(n^3)
long_number get_reverse(const long_number& x, const int prec) {
    if (x.value == "0") {
        std::cout << "Warning! Division by zero!" << std::endl;
        long_number res;
        res.value = "0";
        res.sign = 1;
        res.precision = 0;
        return res;
    } else {
        int res_sign = x.sign;
        int res_precision = prec;
        std::string ans;

        long_number int_x = x;
        int_x.precision = 0;
        int_x.sign = 1;

        int i = 1;
        int after_point = -1;
        long_number cur;
        cur.value = "1";
        int f1 = 1;

        if (cur < int_x ) {
            ans.push_back('0');
            after_point++;
        }

        while (after_point < res_precision && f1 == 1) {
            while (cur.value != "0" && !cur.value.empty() && cur < int_x) {
                cur.value.push_back('0');
                if (cur < int_x ) {
                    ans.push_back('0');
                    after_point++;
                }
                i++;
                int q = 0;
                while (cur.value[q] == '0') {
                    q++;
                }
                cur.value = cur.value.substr(q, cur.value.size() - q);
                if (cur.value.empty()) {
                    f1 = 0;
                }
            }
            if (cur.value != "") {
                int mul = 0;
                while (int_x * (mul + 1) <= cur) {
                    ++mul;
                }
                if (mul > 0) {
                    ans += long_number(mul).value;
                    after_point += long_number(mul).value.size();
                    long_number diff = cur - int_x * mul;
                    cur = diff;
                    if (cur.value == "0") {
                        break;
                    }
                } else {
                    ans += "0";
                    after_point++;
                }

            } else {
                break;
            }

        }

        long_number res;
        res.value = ans;
        res.sign = res_sign;
        res.precision = std::min(res_precision, after_point);
        return res;
    }
}

//overloaded operator /. returns long_number this / y
long_number long_number::operator/(const long_number& y) {

    long_number int_y = y;
    int_y.precision = 0;
    int_y.sign = 1;

    int d = y.value.size() - this->value.size();
    int r = d > 0 ? d : -d;
    long_number rev_y;
    if (r > 0) {
        rev_y = get_reverse(int_y, y.precision + this->precision + r * 20);
    } else {
        rev_y = get_reverse(int_y, y.precision + this->precision + 20);
    }


    long_number rel = simple_mult((*this), rev_y);
    rel.sign = y.sign * this->sign;
    rel.precision -= y.precision;

    int q = 0;
    while (rel.value[q] == '0' && q < rel.value.size() - rel.precision - 1) {
        q++;
    }
    rel.value = rel.value.substr(q, rel.value.size() - q);

    return rel;
}

long_number operator ""_ln(long double x) {
    long_number ret = long_number(x);
    return ret;
}
