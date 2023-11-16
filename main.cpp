#include <iostream>
#include <chrono>
#include <optional>
#include <vector>

#include "poly.h"

std::optional<double> poly_test(polynomial& p1,
                                polynomial& p2,
                                std::vector<std::pair<power, coeff>> solution)

{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // polynomial p3 = p1 * p2;
    polynomial p3 = p1 + 1 ;

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
    std::vector<std::pair<power, coeff>> poly_input1 = {{4,2}, {3,-3}, {2, 5}, {1, 7}, {0, -1}};
    std::vector<std::pair<power, coeff>> poly_input2 = {{6,-4}, {5,2}, {4, -6}, {3, 8}, {2, 1}, {1, -5}, {0, 3}};

    // std::vector<std::pair<power, coeff>> solution = {{4,1}, {2,2}, {0,1}};
    // std::vector<std::pair<power, coeff>> solution_mult = {{10,-8}, {9,16}, {8,-38}, {7, 16}, {6,-34}, {5,-17}, {4, 88}, {3,-35}, {2, -21}, {1, 26}, {0, -3}};
    std::vector<std::pair<power, coeff>> solution_mod = {{3, 29}, {2, 18}, {0, 2}};


    polynomial p1(poly_input1.begin(), poly_input1.end());
    polynomial p2(poly_input2.begin(), poly_input2.end());

    std::optional<double> result = poly_test(p1, p2, solution_mod);

    if (result.has_value())
    {
        std::cout << "Passed test, took " << result.value()/1000 << " seconds" << std::endl;
    } 
    else 
    {
        std::cout << "Failed test" << std::endl;
    }
}