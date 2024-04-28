/**
 * @file main.cpp
 * @author FLESSEL Mélanie,  LI Xinyun
 * @brief 
 * @date 2022-03-14
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <complex>
#include "Nports.hpp"
#include "circuit.hpp"
#include "ij.hpp"
#include "mat.hpp"
#include "matAij.hpp"
#include <iomanip>
#include <cmath>
#include <vector>
#define pi 3.14159

using namespace std;

int main(int argc, const char * argv[]) {
    
    list<Nports*> list_composant;
    /** Lire un fichier SPICE, récupérer les composants */
    circuit circuit;
    string file = "testfile6.txt";
    ifstream fichier(file.c_str(),ios::in);
    circuit.readFile(fichier);
    
    circuit.affichage();
    
    double omega = 2*pi*50;
    circuit.buildSysteme(omega);
    circuit.afficheSysteme();
    
    circuit.setRhs();
    circuit.afficheRhs();
    
    
    vector<complex<double> > x;
    cout << "x : " << endl;
    for (int i = 0; i < 8; i++){
        x.push_back(complex<double>(1.0, 1.0));
        cout << x[i]<< endl;
    } 
    
     
    
    //circuit.clVect(complex<double>(2), &x, complex<double>(3), &x, &x);
   // cout << "x : " << endl;
    /*
    for (int i = 0; i < 8; i++){
        x.push_back(complex<double>(1.0, 1.0));
        cout << x[i]<< endl;
    } */
    
    /*
    complex<double> res_prod = circuit.prodScalair(&x, &x);
    cout << "res " << res_prod << endl; */
    
    //std::vector<std::vector<std::complex<double> > > A{ { 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, 9 } };
    //std::vector<std::vector<std::complex<double> > > B{ { 0, 7, 6 },{ 4, 5, 6 },{ 7, 8, 9 } };
    /* ----   Test cl_vectDevect ---- */
    
    //circuit.cl_vectDevect(2, &A, 1, &B, 0, 0);
    /*
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3 ; j++){
            std::cout << "A " << A[i][j] << std::endl;
        }
    }  */
    
    
    //std::vector<std::complex<double> >C { 2, 4 , 6 };
    /* ----   Test cl_vect_vectDevect ---- */
    /*
    circuit.cl_vect_vectDevect(1, &C, 2, &B, 2);
    for (int i = 0; i < 3 ; i++){
        std::cout << "C " << C[i] << std::endl;
    } */
    
    
    /* ---- Test matvectDevect ---- */
    /*
    vector<std::vector<std::complex<double> > >D{ { 0, 7, 6 },
        { 4, 5, 6 },
        { 7, 8, 9 }, { 1, 2, 3 } ,{0,4,1}, {-1,0,1},{1,1,1},{1,0,0}};
    vector<complex<double> >*r = new vector<complex<double>>;
    circuit.matvectDevect(&D, r, 1);
    for (int i = 0; i < 8 ; i++){
        std::cout << "r " << (*r)[i] << std::endl;
    } */
    
    /* ---- Test prodvectDevect ---- */
    /*
    complex<double> r =  circuit.prodvectDevect(&A, &B, 1);
    cout << " res prodvectDevect " << r << endl;  */
    
    /* ---- Test prod_vect_vectDevecpt ---- */
    /*
    complex<double> r = circuit.prod_vect_vectDevect(&C, &B, 0);
    cout << " res prod_vect_vectDevect " << r << endl;  */
    
    /* ---- Test conjugue ---- */
    /*
    vector<std::vector<std::complex<double> > >E{ { complex<double>(1.0, 1.0), complex<double>(7.0, 1.0), complex<double>(6.0, -1.0) },
        { complex<double>(4.0, 1.0), complex<double>(5.0, 1.0), complex<double>(6.0, 1.0) },
        { complex<double>(7.0, 1.0), complex<double>(8.0, 1.0), complex<double>(9.0, 1.0) } };
    vector<complex<double> >*r = new vector<complex<double>>;
    r = circuit.conjugue(&E, 2);
    cout << " test conjugue " <<endl;
    for (int i = 0; i < E.size() ; i++){
        std::cout << (*r)[i] << std::endl;
    } */
    
    /* ---- Test copie ---- */
    /*
    vector<vector<complex<double> > >* t = new vector<vector<complex<double> > >(8, vector<complex<double>>(8));
    circuit.copie(t, &C, 0);
    for (int i = 0; i < t->size() ; i++){
        cout << " copie de C dasn t "<<  (*t)[i][0] << endl;
    }*/
    
   circuit.solve();
    
    return 0;
}
