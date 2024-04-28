/**
 * @file M.hpp
 * @author  LI Xinyun
 * @brief Inductor component
 * @date 2022-03-14
 *
 */

#include "M.hpp"
#include <iostream>

M::M(int x){
    this->noeud1 = x;
}

M::~M(){
    
}

M::M(const M &other){
    this->noeud1 = other.noeud1;
}


M& M::operator=(const M &other){
    this->noeud1 = other.noeud1;
    return (*this);
}


void M::affiche(){
    std::cout << "Mis à la terre " << this->noeud1 << " " << std::endl;
}


std::string M::type(){
    return "M";
}

std::list<int> M::noeuds(){
    std::list<int> list;
    list.push_back(this->noeud1);
    return list;
}

std::list<std::complex<double> > M::param(){
    std::list<std::complex<double> > list;
    return list;
}
