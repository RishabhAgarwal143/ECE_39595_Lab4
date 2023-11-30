#include <iostream>
#include <chrono>
#include <optional>
#include <vector>
#include <cassert>
#include <string.h>
#include "poly.h"

polynomial readOutputFile(std::string filename) {
    polynomial p1;

    FILE *fp = fopen(filename.c_str(), "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    int coeff;
    int power;

    // fscanf till semicolon
    while (fscanf(fp, "%dx^%d;", &coeff, &power) == 2)
    {

        if (power == 0)
        {
            p1.polynomial_map.at(power) = coeff;
            p1.powers_in_hash.insert(power);
            continue;
        }
        p1.powers_in_hash.insert(power);
        p1.polynomial_map.insert({power, coeff});
    }
    // p1.print();
    return p1;
}

polynomial readFile(std::string filename) {
    // read simple poly.txt till semicolon then rest of the file is poly2
    polynomial p1;
    polynomial p2;
    p2.polynomial_map.clear();
    p2.powers_in_hash.clear();
    p1.polynomial_map.clear();
    p1.powers_in_hash.clear();
    FILE *fp = fopen(filename.c_str(), "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    int coeff;
    int power;

    // fscanf till semicolon
    while (fscanf(fp, "%dx^%d;", &coeff, &power) == 2)
    {

        // if (power == 0)
        // {
        //     p1.polynomial_map.at(power) = coeff;
        //     p1.powers_in_hash.insert(power);
        //     continue;
        // }
        p1.powers_in_hash.insert(power);
        p1.polynomial_map.insert({power, coeff});
    }

    // move cursor by 1;
    fseek(fp, 1, SEEK_CUR);

    while (fscanf(fp, "%dx^%d;", &coeff, &power) == 2) {
        if (power == 0)
        {
            p2.polynomial_map.at(power) = coeff;
            p2.powers_in_hash.insert(power);
        }
        p2.powers_in_hash.insert(power);
        p2.polynomial_map.insert({power, coeff});
    }

    return p1 * p2;
}

std::optional<double> poly_test(polynomial& p1,
                                polynomial& p2,
                                std::vector<std::pair<power, coeff>> solution)

{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // polynomial p3 = p1 * p2;
    polynomial p3 = p1 * p2;

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


    polynomial t1 = readFile("simple_poly.txt");
    polynomial t2 = readOutputFile("result.txt");
    // t1.print();
    auto t11 = t1.canonical_form();

    auto t22 = t2.canonical_form();
    int ct = 0;
    for (int i = 0 ; i < t11.size();i++){
        if(!(t11.at(i) == t22.at(i))){
            std::cout << i << std::endl;
            std::cout << t11.at(i).second << "x^" << t11.at(i).first << " " << t22.at(i).second << "x^" << t22.at(i).first  << "\n"; 
            if (ct == 10) {
                break;
            }
            ct++;
        }
    }
    // std::cout << test << std::endl;
    return 0;





    std::vector<std::pair<power, coeff>> solution = {{2,1}, {1,2}, {0,1}};

    /** This holds (x+1), which we'll pass to each polynomial */
    std::vector<std::pair<power, coeff>> poly_input = {{1,2}, {0,2}, {10,3}};
    std::vector<std::pair<power, coeff>> poly_input1= {{{10,5}, {0,2}, {4, -6}, {3, 8}, {5, 1}, {6, -5}, {2, 3}}};
    polynomial p1(poly_input.begin(), poly_input.end());
    p1.print();
    polynomial p2(poly_input1.begin(), poly_input1.end());
    p2.print();

    std::optional<double> result = poly_test(p1, p2, solution);
    
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


    // if (result.has_value())
    // {
    //     std::cout << "Passed test, took " << result.value()/1000 << " seconds" << std::endl;
    // } 
    // else 
    // {
    //     std::cout << "Failed test" << std::endl;
    // }

    // Test case 1: Divisor is larger than dividend
    std::vector<std::pair<power, coeff>> p333{{0, 1}};
    std::vector<std::pair<power, coeff>> p444{{1, 1}};
    polynomial po1(p333.begin(), p333.end());
    polynomial po2(p444.begin(), p444.end());
    polynomial result1 = po1 % po2;
    assert(result1.canonical_form() == p333);

    // // Test case 2: Divisor is smaller than dividend
    std::vector<std::pair<power, coeff>> p3({{2, 1}, {1, 2}, {0, 1}});
    std::vector<std::pair<power, coeff>> p4({{1, 1}, {0, 1}});
    std::vector<std::pair<power, coeff>> expected({{0, 0}});
    polynomial p31(p3.begin(), p3.end());
    polynomial p41(p4.begin(), p4.end());

    result1 = p31 % p41;
    result1.print();
    assert(result1.canonical_form() == expected);
   
    // std::vector<std::pair<power, coeff>> p5({{2, 1}, {1, 2}, {0, 1}});
    // std::vector<std::pair<power, coeff>> p6({{2, 1}, {1, 2}, {0, 1}});
    // std::vector<std::pair<power, coeff>> expected1({{0, 0}});
    // polynomial p51(p5.begin(), p5.end());
    // polynomial p61(p6.begin(), p6.end());

    // result = p51 % p61;
    // // result.print();
    // assert(result.canonical_form() == expected1);



    // // Test case 4: Dividend is zero polynomial
    // std::vector<std::pair<power, coeff>> p7; // Represents a zero polynomial
    // std::vector<std::pair<power, coeff>> p8({{1, 1}});
    // std::vector<std::pair<power, coeff>> expected3({{0,0}}); // Expected to be a zero polynomial
    // polynomial poly7(p7.begin(), p7.end());
    // polynomial poly8(p8.begin(), p8.end());
    // polynomial result3 = poly7 % poly8;
    // assert(result3.canonical_form() == expected3);

    // // Test case 5: Dividend and divisor have same coefficients but different degrees
    // std::vector<std::pair<power, coeff>> p9({{2, 1}, {1, 2}, {0, 1}});
    // std::vector<std::pair<power, coeff>> p10({{3, 1}, {2, 2}, {1, 1}});
    // std::vector<std::pair<power, coeff>> expected4({{0, 1}});
    // polynomial poly9(p9.begin(), p9.end());
    // polynomial poly10(p10.begin(), p10.end());
    // polynomial result4 = poly9 % poly10;
    // assert(result4.canonical_form() == p9);

    // // Test case 6: Dividend and divisor have same coefficients, same degrees, but different order
    // std::vector<std::pair<power, coeff>> p11({{2, 1}, {0, 2}, {1, 1}});
    // std::vector<std::pair<power, coeff>> p12({{1, 1}, {2, 1}, {0, 2}});
    // std::vector<std::pair<power, coeff>> expected5({{0, 0}});
    // polynomial poly11(p11.begin(), p11.end());
    // polynomial poly12(p12.begin(), p12.end());
    // polynomial result5 = poly11 % poly12;

    // assert(result5.canonical_form() == expected5);

    // // Test case 7: Dividend and divisor are equal
    // std::vector<std::pair<power, coeff>> p13({{5, 2}, {3, 7}, {1, 1},{0, 5}});
    // std::vector<std::pair<power, coeff>> p14({{3, 1},{0,-1}});
    // std::vector<std::pair<power, coeff>> expected6({{2,-2},{1,1},{0,12}}); // Expected to be a zero polynomial
    // polynomial poly13(p13.begin(), p13.end());
    // polynomial poly14(p14.begin(), p14.end());

    // // poly13.print();
    // // poly14.print();
    // polynomial result6 = poly13 % poly14;

    // result6.print();
    // assert(result6.canonical_form() == expected6);

    // std::vector<std::pair<power, coeff>> out({{10,5}, {0,2}, {4, -6}, {3, 8}, {5, 1}, {6, -5}, {2, 3}});
    // std::sort(out.begin(), out.end(), [](const std::pair<power, coeff>& a, const std::pair<power, coeff>& b) {
    //     return a.first > b.first;
    // });

    // auto temp = polynomial(out.begin(), out.end());
    // temp.print();


    // std::vector<std::pair<power, coeff>> p15({{5, 2}, {3, 7}, {1, 1},{0, 5}});
    // std::vector<std::pair<power, coeff>> p16({{0,2}});
    // std::vector<std::pair<power, coeff>> expected7({{2,-2},{1,1},{0,12}}); // Expected to be a zero polynomial
    // polynomial poly15(p15.begin(), p15.end());
    // polynomial poly16(p16.begin(), p16.end());

    // poly15.print();
    // poly16.print();
    // polynomial result7 = poly15 % poly16;

    // result7.print();
    // assert(result7.canonical_form() == p15);

    // std::vector<std::pair<power, coeff>> p17({{3, 5}});
    // std::vector<std::pair<power, coeff>> p18({{2, 6}, {0, 1}});
    // std::vector<std::pair<power, coeff>> expected8({{2,-2},{1,1},{0,12}}); // Expected to be a zero polynomial
    // polynomial poly17(p17.begin(), p17.end());
    // polynomial poly18(p18.begin(), p18.end());

    // poly17.print();
    // poly18.print();
    // polynomial result8 = poly17 % poly18;

    // result8.print();
    // assert(result7.canonical_form() == p16);

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