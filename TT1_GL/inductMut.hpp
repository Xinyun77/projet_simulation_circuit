/**
 * @file inductMut.hpp
 * @author
 * @brief Mutual inductance
 * @date 2022-03-17
 *
 */

#ifndef inductMut_hpp
#define inductMut_hpp

#include <stdio.h>
#include <iostream>
#include <complex>
#include "Nports.hpp"

class inductMut :  public Nports{
protected:
    int noeud1, noeud2, noeud3, noeud4;
    std::complex<double> L1;
    std::complex<double> L2;
    std::complex<double> M;
public:
    inductMut(int = 0, int = 0, int = 0, int = 0, std::complex<double> = 0., std::complex<double> = 0., std::complex<double> = 0.);
    virtual ~inductMut();
    inductMut(const inductMut &other);
    inductMut& operator=(const inductMut &other);
    virtual void affiche();
    virtual std::string type();
    virtual std::list<int> noeuds();
    virtual std::list<std::complex<double> > param();
};
#endif /** inductMut_hpp_ */


