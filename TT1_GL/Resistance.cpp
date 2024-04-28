/**
 * @file Resistance.cpp
 * @author FLESSEL Mélanie
 * @brief Resistor component
 * @date 2022-03-17
 *
 */

#include "Resistance.hpp"

Resistance::Resistance(int noeud1, int noeud2, std::complex<double> R){
    this->noeud1 = noeud1;
    this->noeud2 = noeud2;
    this->r = R;
}

Resistance::~Resistance(){
    
}

Resistance::Resistance(const Resistance &other){
    this->noeud1 = other.noeud1;
    this->noeud2 = other.noeud2;
    this->r = other.r;
}

Resistance& Resistance::operator=(const Resistance &other){
    this->noeud1 = other.noeud1;
    this->noeud2 = other.noeud2;
    this->r = other.r;
    return *this;
}

void Resistance::affiche(){
    std::cout << "RESISTANCE " << this->noeud1 << " " << this->noeud2  << " " << this->r << std::endl;
}

std::string Resistance::type(){
    return "R";
}

std::list<int> Resistance::noeuds(){
    std::list<int> list;
    list.push_back(this->noeud1);
    list.push_back(this->noeud2);
    return list;
}

std::list<std::complex<double> > Resistance::param(){
    std::list<std::complex<double> > list;
    list.push_back(this->r);
    return list;
}
