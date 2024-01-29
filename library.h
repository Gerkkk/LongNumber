#ifndef UNTITLED1_LIBRARY_H
#define UNTITLED1_LIBRARY_H

#include <iostream>
#include <algorithm>


struct long_number {
public:
    std::string value;
    int precision;
    int sign;

    void print_ln();
    [[nodiscard]] long_number abs() const;
    int compare_abs(long_number x);
    bool operator==(const long_number &x);
    bool operator!=(const long_number& x);
    bool operator>(const long_number& x);
    bool operator<(const long_number& x);
    bool operator<=(const long_number& x);
    bool operator>=(const long_number& x);
    long_number promote_precision(const long_number& x);
    long_number sum_abs(long_number x);
    long_number diff_abs(long_number x);
    long_number operator-() const;
    long_number operator+(long_number y);
    long_number operator-(const long_number& y);
    long_number operator*(const long_number& y);
    std::string ln_to_string();
};

long_number simple_mult(const long_number& x, const long_number& y);

#endif //UNTITLED1_LIBRARY_H
