/**
 * @file testSol_1.cpp
 * @author FLESSEL Mélanie,  LI Xinyun
 * @brief 
 * @date 2022-04-05
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
    string file = "testfile3.txt";
    ifstream fichier(file.c_str(),ios::in);
    circuit.readFile(fichier);
    
    circuit.affichage();
    
    double omega = 2*pi*50;
    circuit.buildSysteme(omega);
    circuit.afficheSysteme();
    
    circuit.setRhs();
    circuit.afficheRhs();
    circuit.solve();

    return 0;
}   
    
     