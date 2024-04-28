/**
 * @file Condensateur.cpp
 * @author LI Xinyun 
 * @brief Capacitor component
 * @date 2022-03-17
 *
 */
#include "Condensateur.hpp"

Condensateur::Condensateur(int noeud1, int noeud2, std::complex<double> C){
    this->noeud1 = noeud1;
    this->noeud2 = noeud2;
    this->c = C;
}

Condensateur::~Condensateur(){
    
}

Condensateur::Condensateur(const Condensateur &other){
    this->noeud1 = other.noeud1;
    this->noeud2 = other.noeud2;
    this->c = other.c;
}

Condensateur& Condensateur::operator=(const Condensateur &other){
    this->noeud1 = other.noeud1;
    this->noeud2 = other.noeud2;
    this->c = other.c;
    return *this;
}

void Condensateur::affiche(){
    std::cout << "CONTENSATEUR " << this->noeud1 << " " << this->noeud2 << " " << this->c << std::endl;
}

std::string Condensateur::type(){
    return "C";
}

std::list<int> Condensateur::noeuds(){
    std::list<int> list;
    list.push_back(this->noeud1);
    list.push_back(this->noeud2);
    return list;
}

std::list<std::complex<double> > Condensateur::param(){
    std::list<std::complex<double> > list;
    list.push_back(this->c);
    return list;
}
