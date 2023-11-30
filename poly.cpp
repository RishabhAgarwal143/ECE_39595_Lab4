#include "poly.h"
#include <iostream>
#include <mutex>


polynomial::polynomial()
{
    this->powers_in_hash.insert(0);
    this->polynomial_map.insert({0, 0});
}

template <typename Iter>
polynomial::polynomial(Iter begin, Iter end)
{

    if (begin == end)
    {
        this->powers_in_hash.insert(0);
        this->polynomial_map.insert({0, 0});
        return;
    }
    while (begin->second == 0 && begin != end)
    {
        begin++;
    }
    if (begin == end)
    {
        this->powers_in_hash.insert(0);
        this->polynomial_map.insert({0, 0});
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
    for (int ele = this->powers_in_hash.size() -1  ; ele >= 0; ele--)
    {
        iter--;
        if(this->polynomial_map.at(*iter) == 0){
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
static polynomial _multi(Iter begin, Iter end, polynomial &first, polynomial &second,int i) {

    // multiply bw begin end  
    polynomial p1 = first;
    polynomial p2 = second;
    polynomial out;
    out.powers_in_hash.clear();
    out.polynomial_map.clear();

    // iterate through p1 and p2 sets and multply each term corresponding to the power
    for (auto it1 = begin; it1 != end; it1++)
    {
        for (auto it2 = p2.powers_in_hash.begin(); it2 != p2.powers_in_hash.end(); it2++)
        {
            out.powers_in_hash.insert(*it1 + *it2);
            if (out.polynomial_map.find(*it1 + *it2) != out.polynomial_map.end())
            {
                out.polynomial_map.at(*it1 + *it2) += p1.polynomial_map.at(*it1) * p2.polynomial_map.at(*it2);
            }
            else
            {
                out.polynomial_map.insert({*it1 + *it2, p1.polynomial_map.at(*it1) * p2.polynomial_map.at(*it2)});
            }
        }
    }
    return out;
}

polynomial polynomial::operator*(const polynomial &other) const
{

    std::set<int> new_powers;
    std::unordered_map<int, int> new_map;

    polynomial p1 = *this;
    polynomial p2 = other;
    int size = p1.powers_in_hash.size() < p2.powers_in_hash.size() ? p2.powers_in_hash.size() : p1.powers_in_hash.size();
    bool p1_bigger = p1.powers_in_hash.size() < p2.powers_in_hash.size() ? false : true;
    // return _multi(p1.powers_in_hash.begin(),p1.powers_in_hash.end(),p1,p2,8);
    int num_threads;
    if (size < 100)
    {
        return _multi(this->powers_in_hash.begin(),this->powers_in_hash.end(),p1,p2,9);
    }
    else{
        num_threads =size/100;
    }

    int num_elements_per_thread = size / num_threads;
    int num_elements_last_thread = size % num_threads;

    polynomial result_poly;
    std::mutex result_mutex;

    std::mutex mu;
    auto iter = p1.powers_in_hash.cbegin();
    auto end = p1.powers_in_hash.cend();

    if (!p1_bigger) {
        iter = p2.powers_in_hash.cbegin();
        end = p2.powers_in_hash.cend();
    } 

    std::vector<std::thread> threads;
    for(int i = 0; i < num_threads-1; i++){
        auto start = iter;
        iter  = std::next(iter,num_elements_per_thread);
        auto end = iter;

        if (p1_bigger) {
            threads.emplace_back([&i, &result_poly, &result_mutex, start, end, &p1, &p2, &mu]() {
                auto temp_result = _multi(start, end, p1, p2,i);
                mu.lock();
                result_poly = result_poly + temp_result;
                mu.unlock();
            });
        } else {
            threads.emplace_back([&i, &result_poly, &result_mutex, start, end, &p1, &p2, &mu]() {
                auto temp_result = _multi(start, end, p2, p1,i);
                mu.lock();
                result_poly = result_poly + temp_result;
                mu.unlock();
            });
        }

    }
    auto start = iter;
    if (p1_bigger) {
            threads.emplace_back([&result_poly, &result_mutex, start, end, &p1, &p2, &mu]() {
                auto temp_result = _multi(start, end, p1, p2,8);
                mu.lock();
                result_poly = result_poly + temp_result;
                mu.unlock();
            });
        } else {
            threads.emplace_back([ &result_poly, &result_mutex, start, end, &p1, &p2, &mu]() {
                auto temp_result = _multi(start, end, p2, p1,8);
                mu.lock();
                result_poly = result_poly + temp_result;
                mu.unlock();
            });
        }

    for(auto &t : threads){
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
    auto div_iter = divisor1.powers_in_hash.end();
    div_iter--;
    auto rem_iter = rem.powers_in_hash.end();
    rem_iter--;
    while (rem.find_degree_of() != 0 && (rem.find_degree_of() >= divisor1.find_degree_of()))
    {

        power powerDiff = rem.polynomial_map.at(rem.find_degree_of()) - *div_iter;
        coeff coeffDiff = rem.polynomial_map.at(*rem_iter) / divisor1.polynomial_map.at(*div_iter);

        auto tPair = std::make_pair(powerDiff, coeffDiff);
        std::vector<std::pair<power, coeff>> tVec = {tPair};
        polynomial tPoly = polynomial(tVec.begin(), tVec.end());

        q = q + tPoly;

        rem = rem + ((tPoly * divisor1) * (-1));
        rem_iter = rem.powers_in_hash.end();
        rem_iter--;
    }

    return rem;
}

size_t polynomial::find_degree_of()
{
    auto iter = this->powers_in_hash.end();
    iter--;
    return *iter;
}

std::vector<std::pair<power, coeff>> polynomial::canonical_form() const
{
    std::vector<std::pair<power, coeff>> poly;
    auto iter = this->powers_in_hash.end();
    for (int ele = this->powers_in_hash.size() -1  ; ele >= 0; ele--)
    {
        iter--;
        if(this->polynomial_map.at(*iter) == 0){
            continue;
        }
        poly.push_back(std::make_pair(*iter, this->polynomial_map.at(*iter)));
    }
    return poly;
}