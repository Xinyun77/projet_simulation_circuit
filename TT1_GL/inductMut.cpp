/**
 * @file inductMut.cpp
 * @author FLESSEL Mélanie
 * @brief Mutual inductance
 * @date 2022-03-24
 *
 */

#include "inductMut.hpp"

inductMut::inductMut(int noeud1, int noeud2, int noeud3, int noeud4, std::complex<double> L1, std::complex<double> L2, std::complex<double> M){
    this->noeud1 = noeud1;
    this->noeud2 = noeud2;
    this->noeud3 = noeud3;
    this->noeud4 = noeud4;
    this->L1 = L1;
    this->L2 = L2;
    this->M = M;
}

inductMut::~inductMut(){

}

inductMut::inductMut(const inductMut &other){
    this->noeud1 = other.noeud1;
    this->noeud2 = other.noeud2;
    this->noeud3 = other.noeud3;
    this->noeud4 = other.noeud4;
    this->L1 = other.L1;
    this->L2 = other.L2;
    this->M = other.M;
}

inductMut& inductMut::operator=(const inductMut &other){
    this->noeud1 = other.noeud1;
    this->noeud2 = other.noeud2;
    this->noeud3 = other.noeud3;
    this->noeud4 = other.noeud4;
    this->L1 = other.L1;
    this->L2 = other.L2;
    this->M = other.M;
    return *this;
}

void inductMut::affiche(){
    std::cout << "INDUCTANCE MUTUELLE " << this->noeud1 << " " <<  this->noeud2  << " " << this->noeud3 << " ";
    std::cout <<  this->noeud4  << " " <<this->L1 << " " << this->L2  << " " << this->M << " "<< std::endl;
}


std::string inductMut::type(){
    return "K";
}

std::list<int> inductMut::noeuds(){
    std::list<int> list;
    list.push_back(this->noeud1);
    list.push_back(this->noeud2);
    list.push_back(this->noeud3);
    list.push_back(this->noeud4);
    return list;
}

std::list<std::complex<double> > inductMut::param(){
    std::list<std::complex<double> > list;
    list.push_back(this->L1);
    list.push_back(this->L2);
    list.push_back(this->M);
    return list;
}
