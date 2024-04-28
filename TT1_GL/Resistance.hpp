/**
 * @file Resistance.hpp
 * @author
 * @brief Resistor component
 * @date 2022-03-17
 *
 */

#ifndef Resistance_hpp
#define Resistance_hpp

#include <stdio.h>
#include <iostream>
#include <complex>
#include "Nports.hpp"

class Resistance :  public Nports{
protected:
    int noeud1, noeud2;
    std::complex<double> r;
public:
    Resistance(int = 0, int = 0, std::complex<double> = 0.);
    virtual ~Resistance();
    Resistance(const Resistance &other);
    Resistance& operator=(const Resistance &other);
    virtual void affiche();
    virtual std::string type();
    virtual std::list<int> noeuds();
    virtual std::list<std::complex<double> > param();
};
#endif /* Resistance_hpp */

