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

template <typename Item>
polynomial &polynomial::operator+(const Item &other){
    
}

template <typename Item>
polynomial &polynomial::operator*(const Item &other){

}

template <typename Item>
polynomial &polynomial::operator%(const Item &other){

}



size_t polynomial::find_degree_of(){

}