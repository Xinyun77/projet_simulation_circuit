/**
 * @file Generateur.cpp
 * @author  FLESSEL Mélanie 
 * @brief Voltage source component
 * @date 2022-03-14
 *
 */

#include "Generateur.hpp"
#include <iostream>
#include <complex>


Generateur::Generateur(int noeud1, int noeud2, std::complex<double> E , std::complex<double> Z, std::complex<double> Omega){
    this->noeud1 = noeud1;
    this->noeud2 = noeud2;
    this->E = E;
    this->Z = Z;
    this->Omega = Omega;
}

Generateur::~Generateur(){
    
}

Generateur::Generateur(const Generateur &other){
    this->noeud1 = other.noeud1;
    this->noeud2 = other.noeud2;
    this->E = other.E;
    this->Z = other.Z;
    this->Omega = other.Omega;
}

Generateur& Generateur::operator=(const Generateur &other){
    this->noeud1 = other.noeud1;
    this->noeud2 = other.noeud2;
    this->E = other.E;
    this->Z = other.Z;
    this->Omega = other.Omega;
    return *this;
}

void Generateur::affiche(){
    std::cout << "GENERATEUR " << this->noeud1 << " " <<  this->noeud2  << " " << this->E << " " << this->Z  << " " << this->Omega << " "<< std::endl;
}


std::string Generateur::type(){
    return "Vs";
}

std::list<int> Generateur::noeuds(){
    std::list<int> list;
    list.push_back(this->noeud1);
    list.push_back(this->noeud2);
    return list;
}

std::list<std::complex<double> > Generateur::param(){
    std::list<std::complex<double> > list;
    list.push_back(this->E);
    list.push_back(this->Z);
    list.push_back(this->Omega);
    return list;
}
