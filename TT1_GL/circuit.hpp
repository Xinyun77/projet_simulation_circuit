/**
 * @file circuit.hpp
 * @author  LI Xinyun
 * @date 2022-03-17
 *
 */

#ifndef circuit_hpp
#define circuit_hpp

#include <stdio.h>
#include "Nports.hpp"
#include "ij.hpp"
#include <iostream>
#include <list>
#include <complex>
#include <map>
#include <vector>
#include <fstream>
#include <string>

class circuit{
    std::list<Nports*> liste_compo;  /** liste de composant */
    std::map<ij,std::complex<double> > systeme;   /** Y */
    std::vector<std::complex<double> > rhs;       /** b */
    std::vector<std::complex<double> > sol;       /** x */
    int nb_comp;
    int nb_noeud;
public:
    circuit();
    circuit(const circuit &other);
    circuit operator=(const circuit otehr);
    ~circuit();
    
    //std::list<Nports*> readFile(std::ifstream &fichier);   /** lire , stocker, d'ajouter des composants */
    void readFile(std::ifstream &fichier);
    //void affichage(std::list<Nports*> list);       /** afficher le circuit  electrique */
    void affichage();
    void buildSysteme(double omega);
    void afficheSysteme();
    void setRhs();
    void afficheRhs();
    
    void matVect(std::vector<std::complex<double> >*vect, std::vector<std::complex<double> >*res);
    
    void clVect(std::complex<double> a, std::vector<std::complex<double> >* X, std::complex<double> b, std::vector<std::complex<double> >* Y , std::vector<std::complex<double> >* res); // aX + bY
    
    std::complex<double> prodScalair(std::vector<std::complex<double> >* X, std::vector<std::complex<double> >* Y );
    
    void cl_vectDevect(std::complex<double> a, std::vector<std::vector<std::complex<double> > >*X, std::complex<double> b, std::vector<std::vector<std::complex<double> > >*Y, int colX, int colY);
    
    void cl_vect_vectDevect(std::complex<double> a,std::vector<std::complex<double> >* X, std::complex<double> b,  std::vector<std::vector<std::complex<double> > >*Y, int colY);
    
    void matvectDevect(std::vector<std::vector<std::complex<double> > >*X, std::vector<std::complex<double> >*res, int colX);
    
    std::complex<double> prodvectDevect(std::vector<std::vector<std::complex<double> > >*X, std::vector<std::vector<std::complex<double> > >*Y, int col);
    
    
    std::complex<double> prod_vect_vectDevect(std::vector<std::complex<double> >*X, std::vector<std::vector<std::complex<double> > >*Y, int colY);
    
    std::vector<std::complex<double> >* conjugue(std::vector<std::vector<std::complex<double> > >*X, int colX);
    
    
    void copie(std::vector<std::vector<std::complex<double> > >*X, std::vector<std::complex<double> >*Y, int colX);
    
    void affichageVect(std::vector<std::complex<double> >v );
    
    void solve();
};

#endif /* circuit_hpp */
