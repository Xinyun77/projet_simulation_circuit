/**
 * @file Switch.cpp
 * @author FLESSEL Mélanie
 * @brief Switch component
 * @date 2022-03-18
 *
 */

#include "Switch.hpp"

Switch::Switch(int noeud1, int noeud2, std::complex<double> state){
    this->noeud1 = noeud1;
    this->noeud2 = noeud2;
    this->state = state;
}

Switch::~Switch(){

}

Switch::Switch(const Switch &other){
    this->noeud1 = other.noeud1;
    this->noeud2 = other.noeud2;
    this->state = other.state;
}

Switch& Switch::operator=(const Switch &other){
    this->noeud1 = other.noeud1;
    this->noeud2 = other.noeud2;
    this->state = other.state;
    return *this;
}

void Switch::affiche(){
    std::cout << "SWITCH " << this->noeud1 << " " << this->noeud2;
    if (this->state == 0.){std::cout << " open" << std::endl;}
    if (this->state == 1.){std::cout << " closed" << std::endl;}
}

std::string Switch::type(){
    return "SW";
}

std::list<int> Switch::noeuds(){
    std::list<int> list;
    list.push_back(this->noeud1);
    list.push_back(this->noeud2);
    return list;
}

std::list<std::complex<double> > Switch::param(){
    std::list<std::complex<double> > list;
    list.push_back(this->state);
    return list;
}

