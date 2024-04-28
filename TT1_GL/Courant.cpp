/**
* @file Courant.cpp
* @author FLESSEL Mélanie
* @brief Current source component
* @date 2022-03-18
*
*/

#include "Courant.hpp"
#include <iostream>
#include <complex>

Courant::Courant(int noeud1, int noeud2, std::complex<double> I){
   this->noeud1 = noeud1;
   this->noeud2 = noeud2;
   this->I = I;
}

Courant::~Courant(){

}

Courant::Courant(const Courant &other){
   this->noeud1 = other.noeud1;
   this->noeud2 = other.noeud2;
   this->I = other.I;
}

Courant& Courant::operator=(const Courant &other){
   this->noeud1 = other.noeud1;
   this->noeud2 = other.noeud2;
   this->I = other.I;
   return *this;
}

void Courant::affiche(){
   std::cout << "COURANT " << this->noeud1 << " " << this->noeud2  << " " << this->I << std::endl;
}

std::string Courant::type(){
   return "I";
}

std::list<int> Courant::noeuds(){
   std::list<int> list;
   list.push_back(this->noeud1);
   list.push_back(this->noeud2);
   return list;
}

std::list<std::complex<double> > Courant::param(){
   std::list<std::complex<double> > list;
   list.push_back(this->I);
   return list;
}
