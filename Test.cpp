#include "library.h"

int main() {
    long_number a = {"0234", 3, -1};
    long_number b = {"01", 1, 1};
    long_number c = a * b;
    std::cout << c.ln_to_string() << std::endl;
}