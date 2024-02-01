#include "library.h"

int main() {
    long_number a = 123.0_ln;
    long_number b = -645.34_ln;
    long_number c = a / b;
    std::cout << c.ln_to_string() << std::endl;
}