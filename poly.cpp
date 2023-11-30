#include "poly.h"
#include <iostream>
#include <mutex>

polynomial::polynomial()
{
}

template <typename Iter>
polynomial::polynomial(Iter begin, Iter end)
{

    if (begin == end)
    {
        return;
    }
    while (begin->second == 0 && begin != end)
    {
        begin++;
    }
    if (begin == end)
    {
        return;
    }
    this->powers_in_hash.insert(begin->first);
    this->polynomial_map.insert({begin->first, begin->second});
    begin++;
    while (begin != end)
    {
        if (begin->second == 0)
        {
            begin++;
            continue;
        }

        this->powers_in_hash.insert(begin->first);
        this->polynomial_map.insert({begin->first, begin->second});
        begin++;
    }
}

polynomial::polynomial(const polynomial &other)
{
    this->polynomial_map = other.polynomial_map;
    this->powers_in_hash = other.powers_in_hash;
}

void polynomial::print() const
{
    auto iter = this->powers_in_hash.end();
    for (int ele = this->powers_in_hash.size() - 1; ele >= 0; ele--)
    {
        iter--;
        if (this->polynomial_map.at(*iter) == 0)
        {
            continue;
        }
        std::cout << this->polynomial_map.at(*iter) << "x^" << *iter << " + ";
        // poly.push_back(std::make_pair(*iter, this->polynomial_map.at(*iter)));
    }
    std::cout << "|END|" << std::endl;
}

polynomial &polynomial::operator=(const polynomial &other)
{
    this->polynomial_map.clear();
    this->powers_in_hash.clear();
    this->polynomial_map = other.polynomial_map;
    this->powers_in_hash = other.powers_in_hash;
    return *this;
}

polynomial polynomial::operator+(const polynomial &other) const
{

    polynomial p1 = *this;
    for (auto elem : other.powers_in_hash)
    {
        p1.powers_in_hash.insert(elem);
        if (p1.polynomial_map.find(elem) == p1.polynomial_map.end())
        {
            p1.polynomial_map.insert({elem, other.polynomial_map.at(elem)});
        }
        else
        {
            p1.polynomial_map.at(elem) += other.polynomial_map.at(elem);
        }
        if(p1.polynomial_map.at(elem) == 0){
            p1.powers_in_hash.erase(elem);
            p1.polynomial_map.erase(elem);
        }
    }
    return p1;
}

polynomial polynomial::operator+(const int other) const
{

    polynomial p1 = *this;
    p1.powers_in_hash.insert(0);
    if (p1.polynomial_map.find(0) != p1.polynomial_map.end())
    {
        p1.polynomial_map.at(0) += other;
    }
    else
    {
        p1.polynomial_map.insert({0, other});
    }
    return p1;
}

template <typename Iter>
static polynomial _multi(Iter begin, Iter end,const polynomial &first,const polynomial &second)
{

    polynomial out;
    out.powers_in_hash.clear();
    out.polynomial_map.clear();

    // iterate through p1 and p2 sets and multply each term corresponding to the power
    for (auto it1 = begin; it1 != end; it1++)
    {
        for (auto it2 = second.powers_in_hash.begin(); it2 != second.powers_in_hash.end(); it2++)
        {
            out.powers_in_hash.insert(*it1 + *it2);
            if (out.polynomial_map.find(*it1 + *it2) != out.polynomial_map.end())
            {
                out.polynomial_map.at(*it1 + *it2) += first.polynomial_map.at(*it1) * second.polynomial_map.at(*it2);
            }
            else
            {
                out.polynomial_map.insert({*it1 + *it2, first.polynomial_map.at(*it1) * second.polynomial_map.at(*it2)});
            }
        }
    }
    return out;
}

polynomial polynomial::operator*(const polynomial &other) const
{


    int size = this->powers_in_hash.size() < other.powers_in_hash.size() ? other.powers_in_hash.size() : this->powers_in_hash.size();
    bool p1_bigger = this->powers_in_hash.size() < other.powers_in_hash.size() ? false : true;
    int num_threads;
    if (size < 200)
    {
        // if(p1_bigger){
            return _multi(this->powers_in_hash.begin(), this->powers_in_hash.end(), *this, other);
        // }
        // else{
        //     return _multi(other.powers_in_hash.begin(), other.powers_in_hash.end(), other, *this);
        // }
    }
    else
    {
        num_threads =  8;
    }

    int num_elements_per_thread = size / num_threads;
    int num_elements_last_thread = size % num_threads;

    polynomial result_poly;
    std::mutex mu;
    
    auto iter = this->powers_in_hash.cbegin();
    auto end = this->powers_in_hash.cend();

    if (!p1_bigger)
    {
        iter = other.powers_in_hash.begin();
        end =   other.powers_in_hash.end();
    }

    std::vector<std::thread> threads;
    {
        auto start = iter;
        iter = std::next(iter, num_elements_per_thread);
        auto end = iter;

        if (p1_bigger)
        {
            threads.emplace_back([ &result_poly, start, end, *this, other, &mu]()
                                 {
                auto temp_result = _multi(start, end, *this, other);
                mu.lock();
                result_poly = result_poly + temp_result;
                mu.unlock(); });
        }
        else
        {
            threads.emplace_back([&result_poly, start, end, *this, other, &mu]()
                                 {
                auto temp_result = _multi(start, end, other, *this);
                mu.lock();
                result_poly = result_poly + temp_result;
                mu.unlock(); });
        }
    }
    auto start = iter;
    if (p1_bigger)
    {
        // auto temp_result = _multi(start, end, *this, other);
        // mu.lock();
        // result_poly = result_poly + temp_result;
        // mu.unlock();
        threads.emplace_back([&result_poly, start, end, *this, other, &mu]()
                             {
                auto temp_result = _multi(start, end, *this, other);
                mu.lock();
                result_poly = result_poly + temp_result;
                mu.unlock(); });
    }
    else
    {
        threads.emplace_back([&result_poly, start, end, other, *this, &mu]()
                             {
        auto temp_result = _multi(start, end, other,*this);
        mu.lock();
        result_poly = result_poly + temp_result;
        mu.unlock(); 
                });
    }

    for (auto &t : threads)
    {
        t.join();
    }

    return result_poly;
}

polynomial polynomial::operator*(const int other) const
{
    if (other == 0)
    {
        polynomial p1;
        return p1;
    }
    polynomial p1 = *this;
    for (auto i : this->powers_in_hash)
    {
        p1.polynomial_map.at(i) *= other;
    }
    return p1;
    
}

polynomial operator*(const int val, const polynomial &other)
{
    return other * val;
}
polynomial operator+(const int val, const polynomial &other)
{
    return other + val;
}

polynomial polynomial::operator%(const polynomial &divisor) const
{

    polynomial rem = *this;
    polynomial q;
    polynomial divisor1 = divisor;
    // auto div_iter = divisor1.powers_in_hash.end();
    // div_iter--;
    while (rem.find_degree_of() != 0 && (rem.find_degree_of() >= divisor1.find_degree_of()))
    {
        printf("%ld , %ld \n", rem.find_degree_of(),divisor1.find_degree_of());
        power powerDiff = rem.find_degree_of()- divisor1.find_degree_of();
        coeff coeffDiff = rem.polynomial_map.at(rem.find_degree_of()) / divisor1.polynomial_map.at(divisor1.find_degree_of());

        auto tPair = std::make_pair(powerDiff, coeffDiff);
        std::vector<std::pair<power, coeff>> tVec = {tPair};
        polynomial tPoly = polynomial(tVec.begin(), tVec.end());
        // q = q + tPoly;
        rem = rem + ((divisor1 * tPoly) * (-1));
        break;
    }

    return rem;
}

size_t polynomial::find_degree_of()
{
    auto iter = this->powers_in_hash.end();
    if(iter != this->powers_in_hash.begin())
    {
        iter--;
    }
    return *iter;
}

std::vector<std::pair<power, coeff>> polynomial::canonical_form() const
{
    std::vector<std::pair<power, coeff>> poly;
    auto iter = this->powers_in_hash.end();
    polynomial dummy;

    for (int ele = this->powers_in_hash.size() - 1; ele >= 0; ele--)
    {
        iter--;
        if (this->polynomial_map.at(*iter) == 0)
        {
            continue;
        }
        poly.push_back(std::make_pair(*iter, this->polynomial_map.at(*iter)));
    }
    if(poly.empty()){
        poly.push_back(std::make_pair(0,0));
    }
    return poly;
}