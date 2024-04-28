/**
 * @file Nports.cpp
 * @author
 * @brief Parent class of the circuit components
 * @date 2022-03-07
 *
 */

#include "Nports.hpp"
#include <iostream>

Nports::Nports(int x){
    this->nbports = x;
}

Nports::~Nports(){
    
}

Nports::Nports(const Nports &other){
    this->nbports = other.nbports;
}


Nports& Nports::operator=(const Nports &other){
    this->nbports = other.nbports;
    return (*this);
}



