#include "library.h"

int main() {
    long_number a = -2.345e1;
    long_number b = -0.1e4;
    std::cout << a.ln_to_string() << std::endl;
    long_number c = a + b;
    std::cout << c.ln_to_string() << std::endl;
}