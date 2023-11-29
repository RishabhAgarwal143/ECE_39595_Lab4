#ifndef POLY_H
#define POLY_H

#include <vector>
#include <utility>
#include <cstddef>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <thread>

using power = size_t;
using coeff = int;

class polynomial
{
public:
    std::vector<std::pair<power, coeff>> poly;
    std::set<int> powers_in_hash;
    std::unordered_map<int,int> polynomial_map;

    /**
     * @brief Construct a new polynomial object that is the number 0 (ie. 0x^0)
     *
     */
    polynomial();

    /**
     * @brief Construct a new polynomial object from an iterator to pairs of <power,coeff>
     *
     * @tparam Iter
     *  An iterator that points to a std::pair<power, coeff>
     * @param begin
     *  The start of the container to copy elements from
     * @param end
     *  The end of the container to copy elements from
     */
    template <typename Iter>
    polynomial(Iter begin, Iter end);


    polynomial(std::set<int> power_set,std::unordered_map<int,int> coeff_map);

    /**
     * @brief Construct a new polynomial object from an existing polynomial object
     *
     * @param other
     *  The polynomial to copy
     */
    polynomial(const polynomial &other);

    /**
     * @brief Prints the polynomial.
     *
     * Only used for debugging, isn't graded.
     *
     */
    void print() const;

    /**
     * @brief Turn the current polynomial instance into a deep copy of another
     * polynomial
     *
     * @param other
     * The polynomial to copy
     * @return
     * A reference to the copied polynomial
     */

    polynomial operator+(const polynomial&) const; 
    polynomial operator+(const int) const;
    
    polynomial operator*(const polynomial&) const;
    polynomial operator*(const int) const;

    polynomial operator%(const polynomial&) const;

    polynomial &operator=(const polynomial &other);
    friend polynomial operator+(const int,const polynomial&);
    friend polynomial operator*(const int,const polynomial&);

    // template <typename Item>
    // polynomial &operator+(const Item &other);

    // template <typename Item>
    // polynomial &operator*(const Item &other);
    
    // template <typename Item>
    // polynomial &operator%(const Item &other);

    /**
     * Overload the +, * and % operators. The function prototypes are not
     * provided.
     * 
     * Addition (+) should support
     * 1. polynomial + polynomial
     * 2. polynomial + int
     * 3. int + polynomial
     * 
     * Multiplication (*) should support
     * 1. polynomial * polynomial
     * 2. polynomial * int
     * 3. int * polynomial
     * 
     * Modulo (%) should support
     * 1. polynomial % polynomial
     */
    

    /**
     * @brief Returns the degree of the polynomial
     *
     * @return size_t
     *  The degree of the polynomial
     */
    size_t find_degree_of();

    /**
     * @brief Returns a vector that contains the polynomial is canonical form. This
     *        means that the power at index 0 is the largest power in the polynomial,
     *        the power at index 1 is the second largest power, etc.
     *
     *        ie. x^2 + 7x^4 + 1 would be returned as [(4,7),(2,1),(0,1)]
     *
     *        Note: any terms that have a coefficient of zero aren't returned in
     *        in the canonical form, with one exception.
     *        See the above example (there's no x^3 term, so
     *        there's no entry in the vector for x^3)
     *
     *        The only exception to this is the polynomial 0. If your polynomial is
     *        just the constant 0 then you would return a single entry of [(0,0)]
     *
     *        ie. y = 0 would be returned as [(0,0)]
     *
     * @return std::vector<std::pair<power, coeff>>
     *  A vector of pairs representing the canonical form of the polynomial
     */
    std::vector<std::pair<power, coeff>> canonical_form() const;
};

// polynomial operator+(const polynomial&, const polynomial&); 
// polynomial operator+ (int arg1, const polynomial& arg2);
// polynomial operator+ (const polynomial& arg1, int arg2);

// polynomial operator* (const polynomial& arg1, const polynomial& arg2);
// polynomial operator* (int arg1, const polynomial& arg2);
// polynomial operator* (const polynomial& arg1, int arg2);

// polynomial operator% (const polynomial& arg1, const polynomial& arg2);


#endif
