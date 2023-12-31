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
    // this->powers_in_hash.insert(begin->first);
    this->polynomial_map.insert({begin->first, begin->second});
    this->degree = begin->first;
    begin++;
    while (begin != end)
    {
        if (begin->second == 0)
        {
            begin++;
            continue;
        }

        // this->powers_in_hash.insert(begin->first);
        this->polynomial_map.insert({begin->first, begin->second});
        this->degree = this->degree > begin->first ? this->degree : begin->first;
        begin++;
    }
}

polynomial::polynomial(const polynomial &other)
{
    this->polynomial_map = other.polynomial_map;
    this->degree = other.degree;
    // this->powers_in_hash = other.powers_in_hash;
}

void polynomial::print(std::vector<std::pair<power, coeff>> poly) const
{
    // auto iter = this->powers_in_hash.end();
    for (auto i : poly)
    {
        std::cout << i.second << "x^" << i.first << " +";
    }
    std::cout << std::endl;
    std::cout << "|END|" << std::endl;
}

polynomial &polynomial::operator=(const polynomial &other)
{
    this->polynomial_map.clear();
    this->degree = other.degree;
    this->polynomial_map = other.polynomial_map;
    return *this;
}

polynomial polynomial::operator+(const polynomial &other) const
{
    polynomial p1;
    bool p1_bigger = this->polynomial_map.size() < other.polynomial_map.size() ? false : true;
    if (!p1_bigger)
    {
        p1 = *this;

        for (auto elem : other.polynomial_map)
        {
            // std::cout << "Hey" << (elem.first) << std::endl;
            if (p1.polynomial_map.find(elem.first) == p1.polynomial_map.end())
            {
                // p1.degree = p1.degree > elem.first ? p1.degree : elem.first;
                p1.polynomial_map.insert({elem.first, elem.second});
            }
            else
            {
                p1.polynomial_map[elem.first] += elem.second;
                if (p1.polynomial_map[elem.first] == 0)
                {
                    p1.polynomial_map.erase(elem.first);
                    continue;
                }
                // p1.degree = p1.degree > elem.first ? p1.degree : elem.first;
            }
        }
    }
    else
    {
        p1 = other;

        for (auto elem : this->polynomial_map)
        {
            // std::cout << "Hey" << (elem.first) << std::endl;
            if (p1.polynomial_map.find(elem.first) == p1.polynomial_map.end())
            {
                // p1.degree = p1.degree > elem.first ? p1.degree : elem.first;
                p1.polynomial_map.insert({elem.first, elem.second});
            }
            else
            {
                p1.polynomial_map[elem.first] += elem.second;
                if (p1.polynomial_map[elem.first] == 0)
                {
                    p1.polynomial_map.erase(elem.first);
                    continue;
                }
                // p1.degree = p1.degree > elem.first ? p1.degree : elem.first;
            }
        }
    }
    p1.degree = 0;
    if(this->degree > other.degree){
        p1.degree = this->degree;
    }
    else if(this->degree < other.degree){
        p1.degree = other.degree;
    }
    for (auto i : p1.polynomial_map)
    {
        if (p1.degree < i.first)
        {
            p1.degree = i.first;
        }
    }
    return p1;
}

polynomial polynomial::operator+(const int other) const
{

    polynomial p1 = *this;
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

polynomial polynomial::operator*(const polynomial &other) const
{

    int size = this->polynomial_map.size() < other.polynomial_map.size() ? other.polynomial_map.size() : this->polynomial_map.size();
    bool p1_bigger = this->polynomial_map.size() < other.polynomial_map.size() ? false : true;
    int num_threads;
    if (size < 160)
    {
        polynomial out;
        for (auto it1 = this->polynomial_map.begin(); it1 != this->polynomial_map.end(); it1++)
        {
            for (auto it2 = other.polynomial_map.begin(); it2 != other.polynomial_map.end(); it2++)
            {
                out.polynomial_map[it1->first + it2->first] += it1->second * it2->second;
                // if (out.polynomial_map.find(it1->first + it2->first) != out.polynomial_map.end())
                // {
                // }
                // else
                // {
                //     out.polynomial_map.insert({it1->first + it2->first, it1->second * it2->second});
                // }
            }
        }
        out.degree = this->degree + other.degree;
        return out;
    }
    else
    {
        num_threads = 8;
    }

    int num_elements_per_thread = size / (num_threads);

    polynomial result_poly;
    std::mutex mu;

    auto iter = this->polynomial_map.cbegin();
    auto end1 = this->polynomial_map.cend();

    if (!p1_bigger)
    {
        iter = other.polynomial_map.cbegin();
        end1 = other.polynomial_map.cend();
    }

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; i++)
    {
        auto start = iter;
        iter = std::next(iter, num_elements_per_thread);

        auto end = iter;
        if (i == num_threads - 1)
        {
            end = end1;
        }

        if (p1_bigger)
        {
            threads.emplace_back([&result_poly, start, end, other, &mu]()
                                 {
                polynomial out;
                for (auto it1 = start; it1 != end; it1++)
                {
                    for (auto it2 = other.polynomial_map.begin(); it2 != other.polynomial_map.end(); it2++)
                    {
                        out.polynomial_map[it1->first + it2->first] += it1->second * it2->second;
                        // if (out.polynomial_map.find(it1->first + it2->first) != out.polynomial_map.end())
                        // {
                        // }
                        // else
                        // {
                        //     out.polynomial_map.insert({it1->first + it2->first, it1->second * it2->second});
                        // }
                    }
                }
                mu.lock();
                result_poly = result_poly + out;
                mu.unlock(); });
        }
        else
        {
            threads.emplace_back([&result_poly, start, end, *this, &mu]()
                                 {
                polynomial out;
                for (auto it1 = start; it1 != end; it1++)
                {
                    for (auto it2 = this->polynomial_map.begin(); it2 != this->polynomial_map.end(); it2++)
                    {
                        out.polynomial_map[it1->first + it2->first] += it1->second * it2->second;
                        // if (out.polynomial_map.find(it1->first + it2->first) != out.polynomial_map.end())
                        // {
                        // }
                        // else
                        // {
                        //     out.polynomial_map.insert({it1->first + it2->first, it1->second * it2->second});
                        // }
                    }
                }
                
                mu.lock();
                result_poly = result_poly + out;
                mu.unlock(); });
        }
    }

    for (auto &t : threads)
    {
        t.join();
    }
    result_poly.degree = this->degree + other.degree;
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
    for (auto &i : p1.polynomial_map)
    {
        i.second *= other;
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
    while (rem.find_degree_of() != 0 && (rem.find_degree_of() >= divisor.degree))
    {
        power powerDiff = rem.degree - divisor.degree;
        coeff coeffDiff = rem.polynomial_map.at(rem.degree) / divisor.polynomial_map.at(divisor.degree);
        auto tPair = std::make_pair(powerDiff, coeffDiff);
        std::vector<std::pair<power, coeff>> tVec = {tPair};
        polynomial tPoly = polynomial(tVec.begin(), tVec.end());
        rem = rem + ((divisor * tPoly) * (-1));
    }

    return rem;
}

size_t polynomial::find_degree_of()
{
    return this->degree;
}

std::vector<std::pair<power, coeff>> polynomial::canonical_form() const
{
    std::map<power, int> map;
    for (auto i : this->polynomial_map)
    {
        power x = i.first;
        coeff y = i.second;
        map.insert({x, y});
    }

    std::vector<std::pair<power, coeff>> poly;

    auto ele = map.end();
    while (ele != map.begin())
    {
        ele--;
        poly.push_back(std::make_pair(ele->first, ele->second));
    }
    if (poly.empty())
    {
        poly.push_back(std::make_pair(0, 0));
    }
    return poly;
}