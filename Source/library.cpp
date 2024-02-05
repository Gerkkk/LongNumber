#include "../Headers/library.h"




//prints Lnum::LongNumber given
void Lnum::LongNumber::print_ln() const{
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

//Return Lnum::LongNumber which is an absolute value of given Lnum::LongNumber
[[nodiscard]] Lnum::LongNumber Lnum::LongNumber::abs() const {
    LongNumber ret;
    ret.value = value;
    ret.precision = precision;
    ret.sign = 1;
    return ret;
}

//Compares absolute values of two Lnum::LongNumbers including those with different precisions. Returns 1 if this is greater, -1 if other is greater, 0 otherwise.
int Lnum::LongNumber::compare_abs(Lnum::LongNumber x) const{
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

std::strong_ordering Lnum::LongNumber::operator<=>(const LongNumber &x) const {
    if (sign == x.sign && compare_abs(x) == 0) {
        return std::strong_ordering::equal;
    } else {
        bool res = false;

        if (1 == x.sign && sign == 1) {
            res = compare_abs(x) == 1;
        } else if (-1 == x.sign && sign == -1) {
            res = (compare_abs(x) == -1);
        } else if (sign == 1 && x.sign == -1) {
            if (value == "0" && x.value == "0") {
                res = false;
            } else {
                res = true;
            }
        } else if (sign == -1 && x.sign == 1) {
            res = false;
        }

        if (res) {
            return std::strong_ordering::greater;
        } else {
            return std::strong_ordering::less;
        }
    }
}

//promotes precision of this Lnum::LongNumber to precision of given Lnum::LongNumber by adding 0s to the end
Lnum::LongNumber Lnum::LongNumber::promote_precision(const Lnum::LongNumber& x) const{
    LongNumber ret;
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

//returns long number that equals sum of absolute values of this Lnum::LongNumber and Lnum::LongNumber x
Lnum::LongNumber Lnum::LongNumber::sum_abs(Lnum::LongNumber &x) const{
    Lnum::LongNumber ret;
    Lnum::LongNumber this_c = (*this).promote_precision(x);
    Lnum::LongNumber x_c = x.promote_precision(*this);

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

//returns long number that equals difference of absolute values of this Lnum::LongNumber and Lnum::LongNumber x
Lnum::LongNumber Lnum::LongNumber::diff_abs(Lnum::LongNumber x) const{
    Lnum::LongNumber ret;
    Lnum::LongNumber this_c = (*this).promote_precision(x);
    Lnum::LongNumber x_c = x.promote_precision(*this);

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

//overloaded operator -. returns Lnum::LongNumber -this
Lnum::LongNumber Lnum::LongNumber::operator-() const {
    Lnum::LongNumber ret;
    ret.value = value;
    ret.precision = precision;
    ret.sign = -sign;
    return ret;
}

//overloaded operator +. returns Lnum::LongNumber this + y
Lnum::LongNumber Lnum::LongNumber::operator+(Lnum::LongNumber y) const{
    Lnum::LongNumber ret;
    if (sign == y.sign) {
        Lnum::LongNumber sum = sum_abs(y);
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
            Lnum::LongNumber diff = diff_abs(y);
            ret.value = diff.value;
            ret.precision = diff.precision;
        } else {
            Lnum::LongNumber diff = y.diff_abs(*this);
            ret.value = diff.value;
            ret.precision = diff.precision;
        }
    }
    if (ret.value.empty()) {
        ret.value = "0";
    }
    return ret;
}

//overloaded operator -. returns Lnum::LongNumber this - y
Lnum::LongNumber Lnum::LongNumber::operator-(const Lnum::LongNumber& y) const{
    Lnum::LongNumber ret;
    Lnum::LongNumber sum = (*this) + (-y);
    if (sum.value.empty()) {
        ret.value = "0";
    } else {
        ret.value = sum.value;
    }
    ret.precision = sum.precision;
    ret.sign = sum.sign;
    return ret;
}

//overloaded operator *. returns Lnum::LongNumber this * y
Lnum::LongNumber Lnum::LongNumber::operator*(const Lnum::LongNumber& y) const{
    Lnum::LongNumber prod = simple_mult((*this), y);
    return prod;
}

//returns Lnum::LongNumber this as a string
std::string Lnum::LongNumber::to_string() const{
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

//default constructor. creates Lnum::LongNumber 0;
Lnum::LongNumber::LongNumber(){
    value = "0";
    sign = 1;
    precision = 0;
}

//constructor from int. creates Lnum::LongNumber that equals x;
Lnum::LongNumber::LongNumber(int x) {
    std::string s = std::to_string(std::abs(x));
    sign = (x > 0 ? 1 : -1);
    precision = 0;
    value = s;
}

//constructor from double. creates long number that equals x;
Lnum::LongNumber::LongNumber(long double x) {
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
Lnum::LongNumber::LongNumber(std::string x) {
    int i = 0;
    bool flag_point = false;
    int after_point = 0;
    std::string ret;

    if (x[0] == '-') {
        sign = -1;
        i++;
    } else {
        sign = 1;
    }

    while (i < x.size()) {
        if (x[i] == '.') {
            flag_point = true;
        }

        if (isdigit(x[i])) {
            ret.push_back(x[i]);

            if (flag_point) {
                after_point++;
            }
        }
        i++;
    }

    precision = after_point;
    value = ret;
}

//simple multiplication with complexity o(x^2). returns Lnum::LongNumber = x * y
Lnum::LongNumber Lnum::LongNumber::simple_mult(const Lnum::LongNumber& x, const Lnum::LongNumber& y){
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
        Lnum::LongNumber ret;
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

        Lnum::LongNumber ret;
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

//returns Lnum::LongNumbers that is reverse of given Lnum::LongNumber with given precision.
//complexity is o(n^3)
Lnum::LongNumber Lnum::LongNumber::get_reverse(const Lnum::LongNumber& x, const int prec){
    if (x.value == "0") {
        std::cout << "Warning! Division by zero!" << std::endl;
        Lnum::LongNumber res;
        res.value = "0";
        res.sign = 1;
        res.precision = 0;
        return res;
    } else {
        int res_sign = x.sign;
        int res_precision = prec;
        std::string ans;

        Lnum::LongNumber int_x = x;
        int_x.precision = 0;
        int_x.sign = 1;

        int i = 1;
        int after_point = -1;
        Lnum::LongNumber cur;
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
                while (int_x * Lnum::LongNumber(mul + 1) <= cur) {
                    ++mul;
                }
                if (mul > 0) {
                    ans += Lnum::LongNumber(mul).value;
                    after_point += LongNumber(mul).value.size();
                    Lnum::LongNumber diff = cur - int_x * Lnum::LongNumber(mul);
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

        Lnum::LongNumber res;
        res.value = ans;
        res.sign = res_sign;
        res.precision = std::min(res_precision, after_point);
        return res;
    }
}

//overloaded operator /. returns Lnum::LongNumber this / y
Lnum::LongNumber Lnum::LongNumber::operator/(const Lnum::LongNumber& y) const{

    Lnum::LongNumber int_y = y;
    int_y.precision = 0;
    int_y.sign = 1;

    int d = y.value.size() - this->value.size();
    int r = d > 0 ? d : -d;
    Lnum::LongNumber rev_y;
    if (r > 0) {
        rev_y = get_reverse(int_y, y.precision + this->precision + r * 20);
    } else {
        rev_y = get_reverse(int_y, y.precision + this->precision + 20);
    }


    Lnum::LongNumber rel = simple_mult((*this), rev_y);
    rel.sign = y.sign * this->sign;
    rel.precision -= y.precision;

    int q = 0;
    while (rel.value[q] == '0' && q < rel.value.size() - rel.precision - 1) {
        q++;
    }
    rel.value = rel.value.substr(q, rel.value.size() - q);

    return rel;
}

Lnum::LongNumber operator ""_ln(long double x) {
    Lnum::LongNumber ret = Lnum::LongNumber(x);
    return ret;
}