//
//  M.hpp
//  TT1_GL
//
//  Created by Li Xinyun on 14/03/2022.
//

#ifndef M_hpp
#define M_hpp

/**
 * @file M.cpp
 * @author  LI Xinyun
 * @brief Inductor component
 * @date 2022-03-14
 *
 */

#include <stdio.h>
#include <iostream>
#include <complex>
#include "Nports.hpp"


/** Classe Mis à la terre */
class M : public Nports{
protected:
    int noeud1;
public:
    M(int = 0);
    virtual ~M();
    M(const M &other);
    M& operator=(const M &other);
    virtual void affiche();
    virtual std::string type();
    virtual std::list<int> noeuds();
    virtual std::list<std::complex<double> > param();
};

#endif /* M_hpp */
