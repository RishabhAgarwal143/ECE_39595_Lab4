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
    // std::vector<std::pair<power, coeff>> p1{{0, 1}};
    // std::vector<std::pair<power, coeff>> p2{{1, 1}};
    // polynomial p11(p1.begin(), p1.end());
    // polynomial p12(p2.begin(), p2.end());
    // polynomial result = p11 % p12;
    // assert(result.canonical_form() == p1);

    // Test case 2: Divisor is smaller than dividend
    std::vector<std::pair<power, coeff>> p3({{2, 1}, {1, 2}, {0, 1}});
    std::vector<std::pair<power, coeff>> p4({{1, 1}, {0, 1}});
    std::vector<std::pair<power, coeff>> expected({{0, 0}});
    polynomial p31(p3.begin(), p3.end());
    polynomial p41(p4.begin(), p4.end());

    polynomial result = p31 % p41;
    // result.print();
    assert(result.canonical_form() == expected);
   
    std::vector<std::pair<power, coeff>> p5({{2, 1}, {1, 2}, {0, 1}});
    std::vector<std::pair<power, coeff>> p6({{2, 1}, {1, 2}, {0, 1}});
    std::vector<std::pair<power, coeff>> expected1({{0, 0}});
    polynomial p51(p5.begin(), p5.end());
    polynomial p61(p6.begin(), p6.end());

    result = p51 % p61;
    // result.print();
    assert(result.canonical_form() == expected1);



// Test case 4: Dividend is zero polynomial
std::vector<std::pair<power, coeff>> p7; // Represents a zero polynomial
std::vector<std::pair<power, coeff>> p8({{1, 1}});
std::vector<std::pair<power, coeff>> expected3({{0,0}}); // Expected to be a zero polynomial
polynomial poly7(p7.begin(), p7.end());
polynomial poly8(p8.begin(), p8.end());
polynomial result3 = poly7 % poly8;
assert(result3.canonical_form() == expected3);

// Test case 5: Dividend and divisor have same coefficients but different degrees
std::vector<std::pair<power, coeff>> p9({{2, 1}, {1, 2}, {0, 1}});
std::vector<std::pair<power, coeff>> p10({{3, 1}, {2, 2}, {1, 1}});
std::vector<std::pair<power, coeff>> expected4({{0, 1}});
polynomial poly9(p9.begin(), p9.end());
polynomial poly10(p10.begin(), p10.end());
polynomial result4 = poly9 % poly10;
assert(result4.canonical_form() == p9);

// Test case 6: Dividend and divisor have same coefficients, same degrees, but different order
std::vector<std::pair<power, coeff>> p11({{2, 1}, {0, 2}, {1, 1}});
std::vector<std::pair<power, coeff>> p12({{1, 1}, {2, 1}, {0, 2}});
std::vector<std::pair<power, coeff>> expected5({{0, 0}});
polynomial poly11(p11.begin(), p11.end());
polynomial poly12(p12.begin(), p12.end());
polynomial result5 = poly11 % poly12;

assert(result5.canonical_form() == expected5);

// Test case 7: Dividend and divisor are equal
std::vector<std::pair<power, coeff>> p13({{5, 2}, {3, 7}, {1, 1},{0, 5}});
std::vector<std::pair<power, coeff>> p14({{3, 1},{0,1}});
std::vector<std::pair<power, coeff>> expected6; // Expected to be a zero polynomial
polynomial poly13(p13.begin(), p13.end());
polynomial poly14(p14.begin(), p14.end());

poly13.print();
poly14.print();
polynomial result6 = poly13 % poly14;

result6.print();
assert(result6.canonical_form() == expected5);


// Add more test cases as needed...

    // // Test case 3: Divisor is equal to dividend
    // std::vector<std::pair<power, coeff>> p5({{2, 1}, {1, 2}, {0, 1}});
    // std::vector<std::pair<power, coeff>> p6({{2, 1}, {1, 2}, {0, 1}});
    // expected = polynomial();
    // result = p5 % p6;
    // assert(result == expected);

    // // Test case 4: Dividend is zero polynomial
    // std::vector<std::pair<power, coeff>> p7;
    // std::vector<std::pair<power, coeff>> p8({{1, 1}});
    // expected = polynomial();
    // result = p7 % p8;
    // assert(result == expected);

    // // Test case 5: Divisor is zero polynomial
    // std::vector<std::pair<power, coeff>> p9({{1, 1}});
    // std::vector<std::pair<power, coeff>> p10;
    // try {
    //     result = p9 % p10;
    // } catch (const std::invalid_argument& e) {
    //     assert(std::string(e.what()) == "Division by zero polynomial");
    // }

    // std::cout << "All tests passed!\n";
}