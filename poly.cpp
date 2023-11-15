#include "poly.h"

polynomial::polynomial(){
    std::pair<power, coeff> pair1 = std::make_pair(0, 0);
    this->poly.push_back(pair1);
}

template <typename Iter>
polynomial::polynomial(Iter begin, Iter end){
    
    delete this->poly
    while(begin != end){

    }
}


polynomial::polynomial(const polynomial &other){

}


void polynomial::print() const{

}


polynomial &polynomial::operator=(const polynomial &other){

}

polynomial polynomial::operator+(const polynomial &other){

    std::vector<std::pair<power, coeff>> new_poly;
    std::vector<std::pair<power, coeff>>::iterator it1 = this->poly.begin();
    std::vector<std::pair<power, coeff>>::const_iterator it2 = other.poly.begin();

    while(it1 != this->poly.end() && it2 != other.poly.end()){
        if(it1->first == it2->first){
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
    return polynomial(new_poly.begin(), new_poly.end());
}

polynomial polynomial::operator+(const int other) const{
    std::vector<std::pair<power, coeff>> new_poly;
    for(auto it = this->poly.begin(); it != this->poly.end(); it++){
        new_poly.push_back(std::make_pair(it->first, it->second));
    }
    auto back = this->poly.back();
    if (back.second == 0){
        new_poly.push_back(std::make_pair(0, other));
    }
    else{
        new_poly.push_back(std::make_pair(0, back.second + other));
    }
    return polynomial(new_poly.begin(), new_poly.end());
}

template <typename Item>
polynomial &polynomial::operator*(const Item &other){

}

template <typename Item>
polynomial &polynomial::operator%(const Item &other){

}



size_t polynomial::find_degree_of(){

}