#include "polynomial.h"
#include <cassert>

int main() {

    // Test case 1: Divisor is larger than dividend
    polynomial p1({{0, 1}});
    polynomial p2({{1, 1}});
    polynomial result = p1 % p2;
    assert(result == p1);

    // Test case 2: Divisor is smaller than dividend
    polynomial p3({{2, 1}, {1, 2}, {0, 1}});
    polynomial p4({{1, 1}, {0, 1}});
    polynomial expected({{0, 1}});
    result = p3 % p4;
    assert(result == expected);

    // Test case 3: Divisor is equal to dividend
    polynomial p5({{2, 1}, {1, 2}, {0, 1}});
    polynomial p6({{2, 1}, {1, 2}, {0, 1}});
    expected = polynomial();
    result = p5 % p6;
    assert(result == expected);

    // Test case 4: Dividend is zero polynomial
    polynomial p7;
    polynomial p8({{1, 1}});
    expected = polynomial();
    result = p7 % p8;
    assert(result == expected);

    // Test case 5: Divisor is zero polynomial
    polynomial p9({{1, 1}});
    polynomial p10;
    try {
        result = p9 % p10;
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Division by zero polynomial");
    }

    std::cout << "All tests passed!\n";
}