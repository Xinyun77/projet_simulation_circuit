/**
* @file Courant.hpp
* @author FLESSEL Mélanie
* @brief Current source component
* @date 2022-03-18
*
*/

#ifndef COURANT_HPP
#define COURANT_HPP
#include <stdio.h>
#include <iostream>
#include <complex>
#include "Nports.hpp"

class Courant : public Nports{
protected:
   int noeud1, noeud2;
   std::complex<double> I;

public:
   Courant(int = 0, int = 0, std::complex<double> = 0.);
   virtual ~Courant();
   Courant(const Courant &other);
   Courant& operator=(const Courant &other);
   virtual void affiche();
   virtual std::string type();
   virtual std::list<int> noeuds();
   virtual std::list<std::complex<double> > param();
};
#endif /** COURANT_HPP */
