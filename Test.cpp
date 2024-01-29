#include "library.h"

int main() {
    long_number a = {"1006768798", 6, -1};
    long_number b = {"106768798", 6, -1};
    long_number c = a + b;
    std::cout << c.ln_to_string() << std::endl;
}