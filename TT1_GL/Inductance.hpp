//
//  Inductance.hpp
//  TT1_GL
//
//  Created by Li Xinyun on 14/03/2022.
//

/**
 * @file Inductance.cpp
 * @author  LI Xinyun
 * @brief Inductor component
 * @date 2022-03-14
 *
 */


#ifndef Inductance_hpp
#define Inductance_hpp

#include <stdio.h>
#include <iostream>
#include <complex>
#include "Nports.hpp"

class Inductance : public Nports{
protected:
    int noeud1, noeud2;
    std::complex<double> L;
public:
    Inductance(int = 0, int = 0, std::complex<double> = 0.);
    virtual ~Inductance();
    Inductance(const Inductance &other);
    Inductance& operator=(const Inductance &other);
    virtual void affiche();
    virtual std::string type();
    virtual std::list<int> noeuds();
    virtual std::list<std::complex<double> > param();
};


#endif /* Inductance_hpp */
