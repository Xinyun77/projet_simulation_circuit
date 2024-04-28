/**
 * @file Condensateur.hpp
 * @author  LI Xinyun
 * @brief Capacitor component
 * @date 2022-03-17
 *
 */

#ifndef Condensateur_hpp
#define Condensateur_hpp

#include <stdio.h>
#include <iostream>
#include <complex>
#include <string>
#include "Nports.hpp"

class Condensateur : public Nports{
protected:
    int noeud1, noeud2;
    std::complex<double> c;
public:
    Condensateur(int = 0, int = 0, std::complex<double> = 0.);
    virtual ~Condensateur();
    Condensateur(const Condensateur &other);
    Condensateur& operator=(const Condensateur &other);
    virtual void affiche();
    virtual std::string type();
    virtual std::list<int> noeuds();
    virtual std::list<std::complex<double> > param();
};

#endif /* Condensateur_hpp */


