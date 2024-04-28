/**
 * @file Nports.cpp
 * @author LI Xinyun
 * @brief Parent class of the circuit components
 * @date 2022-03-07
 *
 */

#ifndef Nports_hpp
#define Nports_hpp

#include <stdio.h>
#include <iostream>
#include <list>
#include <complex>

class Nports{
protected :
    int nbports;
public:
    /** constructor, destructor */
    Nports(int = 1);
    virtual ~Nports();
    Nports(const Nports &other);
    Nports& operator=(const Nports &other);
    /** display function */
    virtual void affiche() = 0;
    virtual std::string type() = 0;
    virtual std::list<int> noeuds() = 0;
    virtual std::list<std::complex<double> > param() = 0;
};





#endif /* Nports_hpp */
