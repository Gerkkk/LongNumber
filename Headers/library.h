#ifndef UNTITLED1_LIBRARY_H
#define UNTITLED1_LIBRARY_H

#include <iostream>
#include <algorithm>
#include <compare>
#include <vector>

namespace Lnum {
    struct LongNumber {
    public:
        //constructors
        LongNumber();

        explicit LongNumber(long double x);

        explicit LongNumber(int x);

        explicit LongNumber(std::string x);

        //public methods
        void print_ln() const;

        [[nodiscard]] LongNumber abs() const;

        std::string to_string() const;
        LongNumber mult_mod(const Lnum::LongNumber& y, int &mod);
        LongNumber div_mod(const Lnum::LongNumber& y, int &mod);
        //overloaded operators
        LongNumber operator-() const;

        LongNumber operator+(LongNumber y) const;

        LongNumber operator-(const LongNumber &y) const;

        LongNumber operator*(const LongNumber &y) const;

        LongNumber operator/(const LongNumber &y) const;


        std::strong_ordering operator<=>(const LongNumber &x) const;
        bool operator==(const LongNumber &x) const;
        bool operator!=(const LongNumber &x) const;


    private:
        std::string value;
        int precision;
        int sign;

        //methods
        int compare_abs(LongNumber x) const;

        LongNumber promote_precision(const LongNumber &x) const;

        [[nodiscard]] LongNumber sum_abs(LongNumber &x) const;

        [[nodiscard]] LongNumber diff_abs(LongNumber x) const;

        [[nodiscard]] static LongNumber simple_mult(const LongNumber &x, const LongNumber &y);

        [[nodiscard]] static LongNumber get_reverse(const LongNumber &x, int prec);

    };


}

Lnum::LongNumber operator ""_ln(long double);

#endif //UNTITLED1_LIBRARY_H
