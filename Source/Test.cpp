#include "../Headers/library.h"

int main() {
    using namespace Lnum;
    LongNumber a = 123.0_ln;
    LongNumber b = -645.34_ln;
    LongNumber c = a / b;
    auto d = (a > b);
    std::cout << d << std::endl;
    std::cout << c.to_string() << std::endl;
}