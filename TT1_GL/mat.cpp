/**
* @file mat.cpp
* @author
* @brief matrix class
* @date 2022-03-14
*
*/


#include "mat.hpp"
#include <iostream>

mat::mat(){
    this->row = 0;
    this->colum = 0;
}

mat::mat(int i, int j){
    this->row = i;
    this->colum = j;
}

mat::~mat(){
    
}

mat::mat(const mat& other){
    this->row = other.row;
    this->colum = other.colum;
   
}

mat& mat::operator=(const mat &other){
    this->row = other.row;
    this->colum = other.colum;
    return *this;
}

mat mat::transpose(){
    mat r;
    r.row = this->colum;
    r.colum = this->row;
    return r;
}


