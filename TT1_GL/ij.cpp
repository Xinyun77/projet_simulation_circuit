/**
 * @file ij.cpp
 * @author LI Xinyun
 * @brief Coordinates of matrix elements
 * @date 2022-03-14
 *
 */
#include "ij.hpp"
#include <iostream>
#include <map>
using namespace std;

ij::ij(int i, int j){
    this->i = i;
    this->j = j;
}

ij::~ij(){
    
}

ij::ij(const ij &other){
    this->i = other.i;
    this->j = other.j;
}

ij& ij::operator=(const ij &other){
    this->i = other.i;
    this->j = other.j;
    return (*this);
}

int ij::geti(){
    return this->i;
}

int ij::getj(){
    return this->j;
}

ij ij::swap(){ij I;
    I.i = this->j;
    I.j = this->i;
    return I;
}

std::ostream& operator<<(std::ostream & sortie ,ij &I){
    sortie << "(" << I.i << "," << I.j << ")";
    return sortie;
}




bool ij::estEgale(const ij &other) const{
    return (this->i == other.i && this->j == other.j);
}

bool operator==(ij const &a, ij const &b) {
    return a.estEgale(b);
}
