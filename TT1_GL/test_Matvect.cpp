/**
 * @file main.cpp
 * @author FLESSEL Mélanie,  LI Xinyun
 * @brief 
 * @date 2022-04-03
 *
 */


#include <iostream>
#include <fstream>
#include <string>
#include "circuit.hpp"
#include "Nports.hpp"
#include "complex"
#include "vector"
#include <cmath>
#define pi 3.14159
using namespace std;

int main(){

    list<Nports*> list_composant;
    /** Read a SPICE file, retrieve composants */
    circuit circuit;
    string file = "testfile2.txt";
    ifstream fichier(file.c_str(),ios::in);
    circuit.readFile(fichier);
    
    circuit.affichage();
    
    double omega = 2*pi*50;
    circuit.buildSysteme(omega);
    circuit.afficheSysteme();
    
    circuit.setRhs();
    circuit.afficheRhs();
    
    /** Test of <matrix,vector> */
    vector<complex<double> >x(8,std::complex<double>(1.0,1.0));
    vector<complex<double> >*res = new vector<complex<double> >(8);
    circuit.matVect(&x, res);
    circuit.affichageVect(*res);

    /** Test Linear combination of two vectors */
    vector<std::complex<double> > C (3);
    C[0]=1; C[1]=2; C[2]=3;
    vector<complex<double> >*r = new vector<complex<double> >(3);
    vector<complex<double> >y(3,std::complex<double>(1.0,1.0));
    circuit.clVect(1,&C,-1,&y,r);
    cout << "C : " <<endl;
    circuit.affichageVect(C);
    cout << "y : " <<endl;
    circuit.affichageVect(y);
    cout << "<C> + (-1)*<y> :" <<endl;
    circuit.affichageVect(*r);

    /** Test of Dot product */
    vector<std::complex<double> > a (3);
    a[0]=1; a[1]=2; a[2]=3;
    vector<complex<double> >b(3,std::complex<double>(1.0,1.0));
    cout << " a : " <<endl;
    circuit.affichageVect(a);
    cout << " b : " <<endl;
    circuit.affichageVect(b);
    complex<double>c = circuit.prodScalair(&a, &b);
    cout << "<a,b> : " << c <<endl;

    /** Test Linear combination between two columns of two 2D vectors */
    vector<std::vector<std::complex<double> > > A (3, std::vector<std::complex<double> >(3));
    A[0][0]=1; A[0][1]=2; A[0][2]=3;
    A[1][0]=4; A[1][1]=5; A[1][2]=6;
    A[2][0]=7; A[2][1]=8; A[2][2]=9;

    vector<std::vector<std::complex<double> > > B (3, std::vector<std::complex<double> >(3));
    B[0][0]=5;  B[0][1]=2; B[0][2]=3;
    B[1][0]=48; B[1][1]=5; B[1][2]=6;
    B[2][0]=7;  B[2][1]=8; B[2][2]=23;
    cout << "<A[0][0],A[1][0],A[2][0]> :" <<endl;
    cout << A[0][0] <<endl;
    cout << A[1][0] <<endl;
    cout << A[2][0] <<endl;
    cout << "<B[0][1],B[1][1],B[2][1]> : " <<endl;
    cout << B[0][1] <<endl;
    cout << B[1][1] <<endl;
    cout << B[2][1] <<endl;
    cout << "<A[0][0],A[1][0],A[2][0]> = <A[0][0],A[1][0],A[2][0]> - 2*<B[0][1],B[1][1],B[2][1]> : " <<endl;
    circuit.cl_vectDevect(1, &A, -2, &B, 0, 1);
    cout << A[0][0] <<endl;
    cout << A[1][0] <<endl;
    cout << A[2][0] <<endl;

    /** Test Linear combination between a vector and a column of a 2D vectors */
    vector<std::vector<std::complex<double> > > D (3, std::vector<std::complex<double> >(3));
    D[0][0]=1; D[0][1]=2; D[0][2]=3;
    D[1][0]=4; D[1][1]=5; D[1][2]=6;
    D[2][0]=7; D[2][1]=8; D[2][2]=9;

    vector<std::complex<double> > d (3);
    d[0]=1; d[1]=2; d[2]=3;

    cout << "d : " <<endl;
    circuit.affichageVect(d);
    cout << "<D[0][2],D[1][2],D[2][2]> :" <<endl;
    cout << D[0][2] <<endl;
    cout << D[1][2] <<endl;
    cout << D[2][2] <<endl;
    cout << "2*<d> - <D[0][2],D[1][2],D[2][2]> :" <<endl;
    circuit.cl_vect_vectDevect(2, &d, -1, &D, 2);
    cout << d[0] <<endl;
    cout << d[1] <<endl;
    cout << d[2] <<endl;

    /** Test of Dot product between a matrix and a column of a 2D vector */
    vector<std::vector<std::complex<double> > > E (8, std::vector<std::complex<double> >(3));
    E[0][0]=1; E[0][1]=2; E[0][2]=3;
    E[1][0]=4; E[1][1]=5; E[1][2]=6;
    E[2][0]=7; E[2][1]=8; E[2][2]=9;
    E[3][0]=10; E[3][1]=11; E[3][2]=12;
    E[4][0]=-1; E[4][1]=0; E[4][2]=3;
    E[5][0]=2; E[5][1]=4; E[5][2]=-2;
    E[6][0]=1; E[6][1]=6; E[6][2]=1;
    E[7][0]=3; E[7][1]=-3; E[7][2]=0;

    vector<complex<double> >*resultat = new vector<complex<double> >(8);
    cout << "<matrice_systeme,<E[0][0],E[1][0],.., E[7][0]>> : " <<endl;
    circuit.matvectDevect(&E, resultat, 0);
    circuit.affichageVect(*resultat);

    /** Test of Dot product between two columns of two 2D vectors */
    cout << "<B[0][1],B[1][1],B[2][1]> : " <<endl;
    cout << B[0][1] <<endl;
    cout << B[1][1] <<endl;
    cout << B[2][1] <<endl;
    cout << "<D[0][1],D[1][1],D[2][1]> :" <<endl;
    cout << D[0][1] <<endl;
    cout << D[1][1] <<endl;
    cout << D[2][1] <<endl;
    complex<double> prod;
    prod = circuit.prodvectDevect(&D, &B, 1);
    cout << "<<B[0][1],B[1][1],B[2][1]]>*<D[0][1],D[1][1],D[2][1]> = "<< prod <<endl;

    /** Test of Dot product between a vector and a colomu of a 2D vector */
    cout << "d : " <<endl;
    circuit.affichageVect(d);
    cout << "<D[0][2],D[1][2],D[2][2]> :" <<endl;
    cout << D[0][2] <<endl;
    cout << D[1][2] <<endl;
    cout << D[2][2] <<endl;
    complex<double> dotProd;
    dotProd = circuit.prod_vect_vectDevect(&d, &D, 2);
    cout << "<d, <D[0][2],D[1][2],D[2][2]> > = " << dotProd << endl;

    /**  Test the conjugate of a column in a 2D vetcor */
    vector<complex<double> >*conj = new vector<complex<double> >(3);
    vector<std::vector<std::complex<double> > > F (3, std::vector<std::complex<double> >(3));
    F[0][0]=complex<double>(1.0, -1.0); F[0][1]=complex<double>(2.0, -1.0); F[0][2]=complex<double>(3.0, 1.0);
    F[1][0]=complex<double>(4.0, 1.0); F[1][1]=complex<double>(5.0, 1.0); F[1][2]=complex<double>(6.0, 1.0);
    F[2][0]=complex<double>(7.0, -1.0); F[2][1]=complex<double>(8.0, 1.0); F[2][2]=complex<double>(9.0, -1.0);
    cout << "<F[0][0],F[1][0],F[2][0]> :" <<endl;
    cout << F[0][0] <<endl;
    cout << F[1][0] <<endl;
    cout << F[2][0] <<endl; 
    conj = circuit.conjugue(&F, 0);
    cout << "conjugué de <F[0][0],F[1][0],F[2][0]> " <<endl;
    circuit.affichageVect(*conj);

    /** Test of copie a vector into a column of a 2D vector */
    vector<vector<complex<double> > >* t = new vector<vector<complex<double> > >(8, vector<complex<double> >(3));
    cout << "d : " <<endl;
    cout << d[0] <<endl;
    cout << d[1] <<endl;
    cout << d[2] <<endl;
    cout << "copie d dans la deuxième colonne de t"<< endl;
    circuit.copie(t, &d, 1);
     cout << "<t[0][1],t[1][1],t[2][1]> :" <<endl;
    cout << (*t)[0][1] <<endl;
    cout << (*t)[1][1] <<endl;
    cout << (*t)[2][1] <<endl; 


    return 0;
}