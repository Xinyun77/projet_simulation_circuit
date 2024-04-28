/**
 * @file Inductance.cpp
 * @author  LI Xinyun
 * @brief Inductor component
 * @date 2022-03-14
 *
 */

#include "Inductance.hpp"
#include <iostream>
#include <complex>

Inductance::Inductance(int noeud1, int noeud2, std::complex<double> L){
    this->noeud1 = noeud1;
    this->noeud2 = noeud2;
    this->L = L;
}

Inductance::~Inductance(){
    
}

Inductance::Inductance(const Inductance &other){
    this->noeud1 = other.noeud1;
    this->noeud2 = other.noeud2;
    this->L = other.L;
}

Inductance& Inductance::operator=(const Inductance &other){
    this->noeud1 = other.noeud1;
    this->noeud2 = other.noeud2;
    this->L = other.L;
    return *this;
}

void Inductance::affiche(){
    std::cout << "INDUCTANCE " << this->noeud1 << " " << this->noeud2 << " " <<  this->L << std::endl;
}

std::string Inductance::type(){
    return "L";
}

std::list<int> Inductance::noeuds(){
    std::list<int> list;
    list.push_back(this->noeud1);
    list.push_back(this->noeud2);
    return list;
}

std::list<std::complex<double> > Inductance::param(){
    std::list<std::complex<double> > list;
    list.push_back(this->L);
    return list;
}
