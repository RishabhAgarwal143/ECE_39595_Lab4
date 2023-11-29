#include "poly_copy.h"
#include <iostream>

polynomial::polynomial(){
    this->powers_in_hash.insert(0);
    this->polynomial_map.insert({0,0});
    return;
}

template <typename Iter>
polynomial::polynomial(Iter begin, Iter end){
    
    if(begin == end){
        this->powers_in_hash.insert(0);
        this->polynomial_map.insert({0,0});
        return;
    }
    while(begin->second == 0 && begin != end){
        begin++;
    }
    if(begin == end){
        this->powers_in_hash.insert(0);
        this->polynomial_map.insert({0,0});
        return;
    }
    this->poly.push_back(*begin);
    begin++;
    while(begin != end){
        if(begin->second == 0){
            begin++;
            continue;
        }

        this->powers_in_hash.insert(begin->first);
        this->polynomial_map.insert({begin->first,begin->second});
        begin++;
    }

}

polynomial::polynomial(std::set<int> power_set,std::unordered_map<int,int> coeff_map){
    this->polynomial_map = coeff_map;
    this->powers_in_hash = power_set;
}

polynomial::polynomial(const polynomial &other){
    this->polynomial_map = other.polynomial_map;
    this->powers_in_hash = other.powers_in_hash;
}

void polynomial::print() const{
    for (auto items: this->powers_in_hash){
        std::cout << this->polynomial_map.at(items) << "x^" << items << " + ";
    }
    std::cout << "|END|" <<std::endl;
}


polynomial &polynomial::operator=(const polynomial &other){
    this->polynomial_map.clear();
    this->powers_in_hash.clear();
    this->polynomial_map = other.polynomial_map;
    this->powers_in_hash = other.powers_in_hash;
    return *this;
}

polynomial polynomial::operator+(const polynomial &other) const{

    std::set<int> new_powers;
    std::unordered_map<int,int> new_map;

    // add sets together (find more efficient way to do this)
    new_powers = this->powers_in_hash;
    for(auto elem: other.powers_in_hash){
        new_powers.insert(elem);
    }


    for(auto elem: new_powers){
        int coeff = 0;
        if(this->polynomial_map.find(elem) != this->polynomial_map.end()){
            coeff += this->polynomial_map.at(elem);
        }
        if(other.polynomial_map.find(elem) != other.polynomial_map.end()){
            coeff += other.polynomial_map.at(elem);
        }
        new_map.insert({elem,coeff});
    }

    return polynomial(new_powers,new_map);
}

polynomial polynomial::operator+(const int other) const{
    std::set<int> new_powers;
    std::unordered_map<int,int> new_map;

    // add sets together (find more efficient way to do this)
    new_powers = this->powers_in_hash;
    new_powers.insert(0);

    new_map = this->polynomial_map;
    if (new_map.find(0) != new_map.end()){
        new_map.at(0) += other;
    }
    else{
        new_map.insert({0,other});
    }

    return polynomial(new_powers,new_map);
}


polynomial polynomial::operator*(const polynomial &other) const{
    std::vector<std::pair<power, coeff>> new_poly;
    for(auto it1 = this->poly.begin(); it1 != this->poly.end(); it1++){
        for(auto it2 = other.poly.begin(); it2 != other.poly.end(); it2++){
            new_poly.push_back(std::make_pair(it1->first + it2->first, it1->second * it2->second));
        }
    }

    std::vector<std::pair<power, coeff>>::iterator it1 = new_poly.begin();
    std::vector<std::pair<power, coeff>>::iterator it2 = new_poly.begin();

    while(it1 != new_poly.end()){
        it2 = it1 + 1;
        while(it2 != new_poly.end()){
            if(it1->first == it2->first){
                it1->second += it2->second;
                it2 = new_poly.erase(it2);
            }
            else{
                it2++;
            }
        }
        it1++;
    }
    return polynomial(new_poly.begin(), new_poly.end());
}

polynomial polynomial::operator*(const int other) const{

    if (other == 0)
    {
        polynomial p1;
        return p1;
    }
    
    std::vector<std::pair<power, coeff>> new_poly;
    for(auto it = this->poly.begin(); it != this->poly.end(); it++){
        new_poly.push_back(std::make_pair(it->first, it->second * other));
    }
    return polynomial(new_poly.begin(), new_poly.end());
}

polynomial operator*(const int val,const polynomial& other){
    return other * val;
}
polynomial operator+(const int val,const polynomial& other){
    return other + val;
}

polynomial polynomial::operator%(const polynomial &divisor) const {

    polynomial rem = *this;
    polynomial q;

    while (rem.find_degree_of() != 0 && rem.find_degree_of() >= divisor.poly.at(0).first) {
        power powerDiff = rem.poly.begin()->first - divisor.poly.begin()->first;
        coeff coeffDiff = rem.poly.begin()->second / divisor.poly.begin()->second;

        auto tPair = std::make_pair(powerDiff, coeffDiff);
        std::vector<std::pair<power, coeff>> tVec = {tPair};
        polynomial tPoly = polynomial(tVec.begin(), tVec.end());

        q = q + tPoly;

        rem = rem + ((tPoly * divisor) * (-1));
    }

    return rem;
}


size_t polynomial::find_degree_of(){
    auto iter = this->powers_in_hash.end();
    iter--;
    return *iter;
}

std::vector<std::pair<power, coeff>> polynomial::canonical_form() const{
    std::vector<std::pair<power, coeff>> poly;
    for(auto ele: this->powers_in_hash){
        poly.push_back(std::make_pair(ele,this->polynomial_map.at(ele)));
    }
    return poly;
}