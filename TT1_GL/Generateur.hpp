//
//  Generateur.hpp
//  TT1_GL
//
//  Created by Li Xinyun on 14/03/2022.
//

#ifndef Generateur_hpp
#define Generateur_hpp

/**
 * @file Generateur.cpp
 * @author  FLESSEL Mélanie
 * @brief Voltage source component
 * @date 2022-03-14
 *
 */

#include <stdio.h>
#include <iostream>
#include <complex>
#include "Nports.hpp"

class Generateur : public Nports{
protected:
    int noeud1, noeud2;
    std::complex<double> Z;
    std::complex<double> E;
    std::complex<double> Omega;
public:
    Generateur(int = 0, int = 0, std::complex<double> = 0.,  std::complex<double> = 0., std::complex<double> = 0.);
    virtual ~Generateur();
    Generateur(const Generateur &other);
    Generateur& operator=(const Generateur &other);
    virtual void affiche();
    virtual std::string type();
    virtual std::list<int> noeuds();
    virtual std::list<std::complex<double> > param();
};


#endif /* Generateur_hpp */
