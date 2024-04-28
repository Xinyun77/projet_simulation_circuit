/**
 * @file Switch.hpp
 * @author FLESSEL Mélanie
 * @brief Switch component
 * @date 2022-03-18
 *
 */

#ifndef SWITCH_HPP
#define SWITCH_HPP
#include <iostream>
#include "Nports.hpp"


class Switch : public Nports{
protected:
    int noeud1, noeud2;
    std::complex<double> state; /** 0:open, 1:closed */

public:
    Switch(int = 0, int = 0, std::complex<double> = 0.);
    virtual ~Switch();
    Switch(const Switch&other);
    Switch& operator=(const Switch &other);
    virtual void affiche();
    virtual std::string type();
    virtual std::list<int> noeuds();
    virtual std::list<std::complex<double> > param();
};

#endif /** switch_hpp_ */
