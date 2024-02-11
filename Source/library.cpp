#include "../Headers/library.h"

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

bool Lnum::LongNumber::operator==(const LongNumber &x) const {
    if ((sign == x.sign && compare_abs(x) == 0)) {
        return true;
    } else {
        LongNumber real_x = x;
        LongNumber th = (*this);
        while (real_x.value.back() && real_x.value.back() == '0') {
            real_x.value.pop_back();
            --real_x.precision;
        }
        while (th.value.back() && th.value.back() == '0') {
            th.value.pop_back();
            --th.precision;
        }

        if (th.value == real_x.value && th.value.empty()) {
            return true;
        } else {
            return false;
        }
    }
}

bool Lnum::LongNumber::operator!=(const LongNumber &x) const {
    return !((*this) == x);
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
    std::string add;
    if (ret.precision > ret.value.size()) {
        for(int i = 0;  i < ret.precision - ret.value.size() + 1; i++) {
            add.push_back('0');
        }
    }
    ret.value = add + ret.value;
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
        std::string ans;

        Lnum::LongNumber int_x = x;
        int_x.sign = 1;

        Lnum::LongNumber cur;
        cur.value = "1";

        int q = 0;
        int delta = 0;
        while (int_x.value[q] == '0') {
            q++;
        }

        if (q > 0) {
            std::string new_val;

            for (int i = q; i < int_x.value.size(); i++) {
                new_val.push_back(int_x.value[i]);
            }
            delta = q;
            int_x.precision = int_x.value.size() - q - 1;
            int_x.value = new_val;
        }

        int delta_cur = 0;
        while (cur < int_x) {
            cur.value.push_back('0');
            delta_cur++;
        }

        int tot_dig = 0;
        int shift = delta - delta_cur;
//        std::cout << shift << std::endl;
        while (cur > LongNumber(0) && tot_dig < prec + 1) {
                int mul = 0;

                while (cur > int_x && cur - int_x >= LongNumber(0)) {
                    ++mul;
//                    std::cout << cur.to_string() <<  " " << int_x.to_string() << " " << (cur - int_x).to_string() << std::endl;
                    cur = cur - int_x;
                }
                ans += Lnum::LongNumber(mul).value;
                cur.value.push_back('0');
//                std::cout << "2)" << int_x.to_string() << " " << cur.to_string() << std::endl;
                tot_dig++;

                int f1 = 1;
                for(int  i = 0; i < cur.value.size(); i++) {
                    if (cur.value[i] != '0') {
                        f1 = 0;
                    }
                }
                if (f1 == 1) {
                    while (cur.value.back()) {
                        cur.value.pop_back();
                    }
                    cur.value.push_back('0');
                }
        }
//        std::cout << ans << std::endl;
        Lnum::LongNumber res;
        res.value = ans;
        res.sign = res_sign;
        std::string add;

        res.precision = std::max(prec, (int)ans.size() - 1);
        if (shift > 0) {
            for (int i = 0; i < shift; i++) {
                add.push_back('0');
            }
            res.value = ans + add;
        } else if (shift < 0) {

            res.precision -= shift;
            int t = 0;
            if (res.precision > ans.size() - 1) {
                std::string add1;
                for (int i = 0; i < res.precision - ans.size() + 1; i++) {
                    add1.push_back('0');
                }
                res.value = add1 + res.value;
            }
        }

        return res;
    }
}

Lnum::LongNumber Lnum::LongNumber::mult_mod(const Lnum::LongNumber& y, int &mod) {
    Lnum::LongNumber ans = (*this) * y;
    while (ans.precision > mod) {
        ans.value.pop_back();
        --ans.precision;
    }
    return ans;
}

Lnum::LongNumber Lnum::LongNumber::div_mod(const Lnum::LongNumber& y, int &mod) {
    Lnum::LongNumber int_y = y;
    int_y.sign = 1;

    LongNumber rev_y = get_reverse(int_y, mod);
    LongNumber rel = simple_mult((*this), rev_y);

    while (rel.precision > mod) {
        rel.value.pop_back();
        --rel.precision;
    }
    return rel;
}

//overloaded operator /. returns Lnum::LongNumber this / y
Lnum::LongNumber Lnum::LongNumber::operator/(const Lnum::LongNumber& y) const{

    Lnum::LongNumber int_y = y;
    int_y.sign = 1;

    LongNumber rev_y = get_reverse(int_y, 50);
    LongNumber rel = simple_mult(*this, rev_y);
    return rel;
}

Lnum::LongNumber operator ""_ln(long double x) {
    Lnum::LongNumber ret = Lnum::LongNumber(x);
    return ret;
}