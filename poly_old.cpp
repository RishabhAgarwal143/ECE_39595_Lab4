#include "poly.h"
#include <iostream>

polynomial::polynomial(){
    std::pair<power, coeff> pair1 = std::make_pair(0, 0);
    this->poly.push_back(pair1);
}

template <typename Iter>
polynomial::polynomial(Iter begin, Iter end){
    
    if(begin == end){
        std::pair<power, coeff> pair1 = std::make_pair(0, 0);
        this->poly.push_back(pair1);
        return;
    }
    while(begin->second == 0 && begin != end){
        begin++;
    }
    if(begin == end){
        std::pair<power, coeff> pair1 = std::make_pair(0, 0);
        this->poly.push_back(pair1);
        return;
    }
    this->poly.push_back(*begin);
    begin++;

    while(begin != end){
        if(begin->second == 0){
            begin++;
            continue;
        }
        auto temp = this->poly.begin();
        auto temp2 = this->poly.end();
        while(temp != temp2){
            if(temp->first < begin->first){
                this->poly.insert(temp,*begin);
                break;
            }
            temp++;
        }
        if(temp == temp2){
            this->poly.push_back(*begin);
        }
        begin++;
    }

}

polynomial::polynomial(const polynomial &other){
    for (auto i: other.poly){
        this->poly.push_back(i);
    }
}

void polynomial::print() const{
    for (auto items: this->poly){
        std::cout << items.second << "x^" << items.first << " + ";
    }
    std::cout << "|END|" <<std::endl;
}


polynomial &polynomial::operator=(const polynomial &other){
    this->poly.clear();
    for (auto i: other.poly){
        this->poly.push_back(i);
    }
    return *this;
}

polynomial polynomial::operator+(const polynomial &other) const{

    std::vector<std::pair<power, coeff>> new_poly;
    std::vector<std::pair<power, coeff>>::const_iterator it1 = this->poly.begin();
    std::vector<std::pair<power, coeff>>::const_iterator it2 = other.poly.begin();

    while(it1 != this->poly.end() && it2 != other.poly.end()){
        if(it1->first == it2->first){
            if (it1->second + it2->second == 0){
                it1++;
                it2++;
                continue;
            }
            new_poly.push_back(std::make_pair(it1->first, it1->second + it2->second));
            it1++;
            it2++;
        }
        else if(it1->first > it2->first){
            new_poly.push_back(std::make_pair(it1->first, it1->second));
            it1++;
        }
        else{
            new_poly.push_back(std::make_pair(it2->first, it2->second));
            it2++;
        }
    }

    while(it1 != this->poly.end()){
        new_poly.push_back(*it1);
        it1++;
    }
    while(it2 != other.poly.end()){
        new_poly.push_back(*it2);
        it2++;
    }

    return polynomial(new_poly.begin(), new_poly.end());
}

polynomial polynomial::operator+(const int other) const{
    std::vector<std::pair<power, coeff>> new_poly;
    for(auto it = this->poly.begin(); it != this->poly.end(); it++){
        new_poly.push_back(std::make_pair(it->first, it->second));
    }

    if (other == 0) {
        return polynomial(new_poly.begin(), new_poly.end());
    }

    auto back = this->poly.back();

    if (back.first == 0){
        new_poly.pop_back();
        new_poly.push_back(std::make_pair(0, back.second +other));
    }
    else{
        new_poly.push_back(std::make_pair(0, other));
    }
    return polynomial(new_poly.begin(), new_poly.end());
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
    return this->poly.at(0).first;
}

std::vector<std::pair<power, coeff>> polynomial::canonical_form() const{
    
    return this->poly;
}