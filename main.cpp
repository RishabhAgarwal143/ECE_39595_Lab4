#include <iostream>
#include <chrono>
#include <optional>
#include <vector>
#include <cassert>

#include "poly.h"

std::optional<double> poly_test(polynomial& p1,
                                polynomial& p2,
                                std::vector<std::pair<power, coeff>> solution)

{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // polynomial p3 = p1 * p2;
    polynomial p3 = p1 + p2;

    auto p3_can_form = p3.canonical_form();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    p3.print();

    if (p3_can_form != solution)
    {
        return std::nullopt;
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

int main()
{
    /** We're doing (x+1)^2, so solution is x^2 + 2x + 1*/
    // std::vector<std::pair<power, coeff>> solution = {{2,1}, {1,2}, {0,1}};

    // /** This holds (x+1), which we'll pass to each polynomial */
    // std::vector<std::pair<power, coeff>> poly_input = {{1,1}, {0,1}};
    // polynomial p1(poly_input.begin(), poly_input.end());
    // polynomial p2(poly_input.begin(), poly_input.end());

    // std::vector<std::pair<power, coeff>> poly_input1 = {{7, 1}};
    // std::vector<std::pair<power, coeff>> poly_input1 = {{10,-5}};
    // std::vector<std::pair<power, coeff>> poly_input2 = {{10,5}, {0,2}, {4, -6}, {3, 8}, {5, 1}, {6, -5}, {2, 3}};

    // std::vector<std::pair<power, coeff>> solution = {{4,1}, {2,2}, {0,1}};
    // std::vector<std::pair<power, coeff>> solution_mult = {{10,-8}, {9,16}, {8,-38}, {7, 16}, {6,-34}, {5,-17}, {4, 88}, {3,-35}, {2, -21}, {1, 26}, {0, -3}};
    // std::vector<std::pair<power, coeff>> solution_mod = {{3, 29}, {2, 18}, {0, 2}};

    // make testcases for mod 
    // std::vector<std::pair<power, coeff>> poly_input1 = {{10,5}, {0,2}, {4, -6}, {3, 8}, {5, 1}, {6, -5}, {2, 3}};
    // std::vector<std::pair<power, coeff>> poly_input2 = {{10,5}, {0,2}, {4, -6}, {3, 8}, {5, 1}, {6, -5}, {2, 3}};
    // std::vector<std::pair<power, coeff>> solution_mod = {{3, 29}, {2, 18}, {0, 2}};




    // polynomial p1(poly_input1.begin(), poly_input1.end());
    // polynomial p2(poly_input2.begin(), poly_input2.end());
    // p1.print();
    // p2.print();

    // std::optional<double> result = poly_test(p1, p2, solution_mod);

    // if (result.has_value())
    // {
    //     std::cout << "Passed test, took " << result.value()/1000 << " seconds" << std::endl;
    // } 
    // else 
    // {
    //     std::cout << "Failed test" << std::endl;
    // }

    // Test case 1: Divisor is larger than dividend
    std::vector<std::pair<power, coeff>> p1({{0, 1}});
    std::vector<std::pair<power, coeff>> p2({{1, 1}});
    std::vector<std::pair<power, coeff>> result = p1 % p2;
    assert(result == p1);

    // Test case 2: Divisor is smaller than dividend
    std::vector<std::pair<power, coeff>> p3({{2, 1}, {1, 2}, {0, 1}});
    std::vector<std::pair<power, coeff>> p4({{1, 1}, {0, 1}});
    std::vector<std::pair<power, coeff>> expected({{0, 1}});
    result = p3 % p4;
    assert(result == expected);

    // Test case 3: Divisor is equal to dividend
    std::vector<std::pair<power, coeff>> p5({{2, 1}, {1, 2}, {0, 1}});
    std::vector<std::pair<power, coeff>> p6({{2, 1}, {1, 2}, {0, 1}});
    expected = polynomial();
    result = p5 % p6;
    assert(result == expected);

    // Test case 4: Dividend is zero polynomial
    std::vector<std::pair<power, coeff>> p7;
    std::vector<std::pair<power, coeff>> p8({{1, 1}});
    expected = polynomial();
    result = p7 % p8;
    assert(result == expected);

    // Test case 5: Divisor is zero polynomial
    std::vector<std::pair<power, coeff>> p9({{1, 1}});
    std::vector<std::pair<power, coeff>> p10;
    try {
        result = p9 % p10;
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Division by zero polynomial");
    }

    std::cout << "All tests passed!\n";
}