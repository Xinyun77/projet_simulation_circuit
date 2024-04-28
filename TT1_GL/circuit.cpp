/**
 * @file circuit.cpp
 * @author  LI Xinyun
 * @brief Creation and display of electrical circuits, from the reading of a txt file
 * @date 2022-03-17
 *
 */

#include "circuit.hpp"
#include "Inductance.hpp"
#include "Generateur.hpp"
#include "Resistance.hpp"
#include "M.hpp"
#include "Condensateur.hpp"
#include "Courant.hpp"
#include "Switch.hpp"
#include "inductMut.hpp"
#include "matAij.hpp"
#include "ij.hpp"
#include <iostream>
#include <string>
#include <complex>
#include <algorithm>

circuit::circuit(){
    
}

circuit::~circuit(){
    
}

circuit::circuit(const circuit &other){
    
}

void circuit::readFile(std::ifstream & fichier){
    std::list<Nports*> list_Nports;
    Nports* composant;
    this->nb_comp = 0;                              /**initialize the number of components to 0*/
    if (fichier.is_open()){
        std::string line;
        std::vector<int> listNoeud;
        listNoeud.push_back(0);
        while (getline(fichier, line)) {
            std::string noeud;
            fichier >> noeud;                       /** stocks the first word in node */
            /** if string is VOLTAGE SOURCE */
            if(!noeud.compare("Vs")){
                this->nb_comp++;                    /**updating the number of components*/
                int noeud1, noeud2;                 /** VS nodes */
                std::complex<double> Z;
                std::complex<double> E;             /** VS parameters */
                std::complex<double> Omega;
                fichier >> noeud1 >> noeud2 >> E >> Z >> Omega;
                if (noeud1 > listNoeud.back()){     /** if the node is not already in the list, it is added */
                    listNoeud.push_back(noeud1);
                }
                if (noeud2 > listNoeud.back()){     /** if the node is not already in the list, it is added */
                    listNoeud.push_back(noeud2);
                }
                composant = new Generateur(noeud1, noeud2, E, Z, Omega);
                if (composant != nullptr){          /** if pointer is not null, it is added to the component list */
                    this->liste_compo.push_back(composant);
                }
                else{
                    composant = nullptr;
                }
            }
            
            /** si string est INDUCTANCE */
            if (!noeud.compare("L")){               /** if string is INDUCTANCE */
                this->nb_comp++;
                int noeud1, noeud2;                 /** INDUCTANCE nodes */
                std::complex<double> L;             /** INDUCTANCE parameters */
                fichier >> noeud1 >> noeud2 >> L;
                if (noeud1 > listNoeud.back()){
                    listNoeud.push_back(noeud1);
                }
                if (noeud2 > listNoeud.back()){
                    listNoeud.push_back(noeud2);
                }
                composant = new Inductance(noeud1,noeud2,L);
                if (composant != nullptr){          /** if pointer is not null, it is added to the component list */
                    this->liste_compo.push_back(composant);
                }
                else{
                    composant = nullptr;
                }
            }
            /** if string is RESISTANCE */
            if (!noeud.compare("R")){
                this->nb_comp++;
                int noeud1, noeud2;                 /** RESISTANCE nodes */
                std::complex<double> R;             /** RESISTANCE parameters */
                fichier >> noeud1 >> noeud2 >> R;
                if (noeud1 > listNoeud.back()){
                    listNoeud.push_back(noeud1);
                }
                if (noeud2 > listNoeud.back()){
                    listNoeud.push_back(noeud2);
                }
                composant = new Resistance(noeud1,noeud2,R);
                if (composant != nullptr){          /** if pointer is not null, it is added to the component list */
                    this->liste_compo.push_back(composant);
                }
                else{
                    composant = nullptr;
                }
            }
            /** if string is CAPACITOR */
            if (!noeud.compare("C")){
                this->nb_comp++;
                int noeud1, noeud2;
                std::complex<double> C;
                fichier >> noeud1 >> noeud2 >> C;
                if (noeud1 > listNoeud.back()){
                    listNoeud.push_back(noeud1);
                }
                if (noeud2 > listNoeud.back()){
                    listNoeud.push_back(noeud2);
                }
                composant = new Condensateur(noeud1,noeud2,C);
                if (composant != nullptr){              /** if pointer is not null, it is added to the component list */
                    this->liste_compo.push_back(composant);
                }
                else{
                    composant = nullptr;
                }
            }
            if (!noeud.compare("I")){   /** if string is CURRENT SOURCE */
                this->nb_comp++;
                ///std::cout << "COURANT" << std::endl;
                int noeud1, noeud2;
                std::complex<double> I;
                fichier >> noeud1 >> noeud2 >> I;
                if (noeud1 > listNoeud.back())listNoeud.push_back(noeud1);
                if (noeud2 > listNoeud.back())listNoeud.push_back(noeud2);

                composant = new Courant(noeud1,noeud2,I);
                if (composant != nullptr){  /** if pointer is not null, it is added to the component list */
                    this->liste_compo.push_back(composant);
                }
                else{
                    composant = nullptr;
                }
            }
            if (!noeud.compare("SW")){  /** if string is SWITCH*/
                this->nb_comp++;
                ///std::cout << "SWITCH" << std::endl;
                int noeud1, noeud2;
                std::complex<double> state;
                fichier >> noeud1 >> noeud2 >> state;
                if (noeud1 > listNoeud.back())listNoeud.push_back(noeud1);
                if (noeud2 > listNoeud.back())listNoeud.push_back(noeud2);

                composant = new Switch(noeud1,noeud2,state);
                if (composant != nullptr){  /** if pointer is not null, it is added to the component list */
                    this->liste_compo.push_back(composant);
                }
                else{
                    composant = nullptr;
                }
            }
            if (!noeud.compare("K")){   /** if string is MUTUAL INDUCTANCE*/
                this->nb_comp++;
                int noeud1, noeud2, noeud3, noeud4;
                std::complex<double> L1, L2, M;
                fichier >> noeud1 >> noeud2 >> noeud3 >> noeud4 >> L1 >> L2 >> M;
                if (noeud1 > listNoeud.back())listNoeud.push_back(noeud1);
                if (noeud2 > listNoeud.back())listNoeud.push_back(noeud2);
                if (noeud3 > listNoeud.back())listNoeud.push_back(noeud3);
                if (noeud4 > listNoeud.back())listNoeud.push_back(noeud4);

                composant = new inductMut(noeud1, noeud2, noeud3, noeud4, L1, L2, M);
                if (composant != nullptr){  /** if pointer is not null, it is added to the component list */
                    this->liste_compo.push_back(composant);
                }
                else{
                    composant = nullptr;
                }
            }

            
            this->nb_noeud = (int)listNoeud.size() - 1;  /** ajouter nombre de noeud dans circuit */
            /** si string est Mis a la terre */
            if (!noeud.compare("T")){
                this->nb_comp++;
                int noeud1;
                fichier >> noeud1 ;
                composant = new M(noeud1);
                if (composant != nullptr){              /** si le pointeur n'est pas null , on l'ajoute dans la liste de composant */
                    this->liste_compo.push_back(composant);
                }
                else{
                    composant = nullptr;
                }
            }
        }
        fichier.close();
    }
}


void circuit::affichage(){
    std::cout << "ICI, affichage de composant dans le circuit :) " << std::endl;
    std::cout << "- - - - - - - - - - " << std::endl;
    std::list<Nports*>::iterator it;
    for (it = this->liste_compo.begin();it != this->liste_compo.end();it++){
        (*it)->affiche();
    }
}


void circuit::buildSysteme(double omega){
    std::list<Nports*>::iterator itthis;  /** iterator points to this */
    /** browse of the component list */
    std::list<Nports*>::iterator itM;
    //itM = this->liste_compo.rbegin();
    int nm_ligne = 0;                              /** initialization of the row counter to 0 */
    int nb_comp = this->nb_comp; 
    int cpt = 0;
    for (auto itM = this->liste_compo.begin(); itM != this->liste_compo.end(); itM++ ){
        if ((*itM)->type() == "M"){               /** if earthing is in list, it is added to matrix first row and column */
        /** insert 1 at (nm_ligne,(*itM)->noeuds().front() - 1) */
        ij I(nm_ligne,(*itM)->noeuds().front() - 1);
        this->systeme.insert(std::pair<ij,std::complex<double> >(I,1));
        cpt++;
        if (cpt > 1){nm_ligne++;}
        nb_comp-= 1;
        }
    }                  
    
    std::list<Nports*>::iterator itK;
    for (auto itK = this->liste_compo.begin(); itK != this->liste_compo.end(); itK++){
        /** if MUTUAL INDUCTANCE is in the list of component */ 
        if ((*itK)->type() == "K"){
           // nb_ligne = (this->nb_comp - 1)*2 + 6 + this->nb_noeud;
           nb_comp = this->nb_comp ;
        }
    } 
    int nb_ligne = 2*nb_comp + this->nb_noeud;   /// matrix last row is removed to obtain a square matrix de nb_ligne * nb_ligne
    for (itthis = this->liste_compo.begin(); itthis != this->liste_compo.end(); itthis++){ /** parcourir la lsite de composant */
        if ((*itthis)->type() != "M"){
        int noeud1, noeud2;
        std::complex<double> param;
        if ((*itthis)->type() == "Vs"){             /** if component is VOLTAGE SOURCE, its nodes and parameters are taken */
            nm_ligne++;                             /** updating rows counter */
            std::complex<double> Z;
            std::list<std::complex<double> >l;  /** creat a new list l */
            l = (*itthis)->param();             /** l points to list of parametre */
            l.pop_front();                      /** Zparameter is removed to get the two others */
            Z = l.front();
            noeud1 = (*itthis)->noeuds().front();   /** the node number is the column in the matrix */
            noeud2 = (*itthis)->noeuds().back();
            /** Kirchhoff's second law (voltage law) */
            ij Vs_n1(nm_ligne, noeud1 - 1);              /** coordinates of v_noeud1 */
            ij Vs_n2(nm_ligne, noeud2 - 1);             /** coordinates of v_noeud2 */
            this->systeme.insert(std::pair<ij,std::complex<double> >(Vs_n1, -1));
            this->systeme.insert(std::pair<ij,std::complex<double> >(Vs_n2, 1));
            if (Z != std::complex<double>(0)){
            ij i_E1(nm_ligne, 2*nm_ligne + this->nb_noeud -2);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_E1, -Z));}
            /** component current */
            ij i_E1_(nm_ligne + nb_comp, 2*nm_ligne + this->nb_noeud -2);
            ij i_E2(nm_ligne + nb_comp, 2*nm_ligne + this->nb_noeud - 1);
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_E1_, 1));
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_E2, 1));
            /** Kirchhoff's first law (nodal rule) */
            if (2*nb_comp + noeud1 < nb_ligne){  /** row of noeud1 */
                ij i_1(2*nb_comp + noeud1 , 2*nm_ligne + this->nb_noeud - 2);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_1, 1));
            }
            if (2*nb_comp + noeud2 < nb_ligne){
                ij i_2(2*nb_comp + noeud2 , 2*nm_ligne + this->nb_noeud - 1);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_2, 1));
            }
        }
        
        if ((*itthis)->type() == "L"){                /** if component is INDUCTANCE, its nodes and parameters are taken */
            nm_ligne++;  // incrémenter la ligne
            noeud1 = (*itthis)->noeuds().front();    /** the node number is the column in the matrix */
            noeud2 = (*itthis)->noeuds().back();
            param = (*itthis)->param().front();
            /** Kirchhoff's second law (voltage law) */
            ij L_n1(nm_ligne, noeud1 - 1);
            ij L_n2(nm_ligne, noeud2 - 1);
            this->systeme.insert(std::pair<ij,std::complex<double> >(L_n1, -1));
            this->systeme.insert(std::pair<ij,std::complex<double> >(L_n2, 1));
            ij i_L1(nm_ligne, 2*nm_ligne + this->nb_noeud -2);
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_L1, -param*std::complex<double>(0.0,1.0)*omega));
            /** component current */
            ij i_L1_(nm_ligne + nb_comp, 2*nm_ligne + this->nb_noeud -2);
            ij i_L2(nm_ligne + nb_comp, 2*nm_ligne + this->nb_noeud - 1);
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_L1_, 1));
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_L2, 1));
            /** Kirchhoff's first law (nodal rule) */
            if (2*nb_comp + noeud1 < nb_ligne){       /** row of noeud1 */
                ij i_1(2*nb_comp + noeud1 , 2*nm_ligne + this->nb_noeud - 2);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_1, 1));
            }
            if (2*nb_comp + noeud2 < nb_ligne){
                ij i_2(2*nb_comp + noeud2 , 2*nm_ligne + this->nb_noeud - 1);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_2, 1));
            }
           
        }
        
        if ((*itthis)->type() == "R"){                /** if component is RESISTANCE, its nodes and parameters are taken */
            nm_ligne++;
            noeud1 = (*itthis)->noeuds().front();    /** the node number is the column in the matrix */
            noeud2 = (*itthis)->noeuds().back();
            param = (*itthis)->param().front();
            /** Kirchhoff's second law (voltage law) */
            ij R_n1(nm_ligne, noeud1 - 1);
            ij R_n2(nm_ligne, noeud2 - 1);
            this->systeme.insert(std::pair<ij,std::complex<double> >(R_n1, -1));
            this->systeme.insert(std::pair<ij,std::complex<double> >(R_n2, 1));
            ij i_R1(nm_ligne, 2*nm_ligne + this->nb_noeud -2);
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_R1, -param));
            /** component current */
            ij i_R1_(nm_ligne + nb_comp, 2*nm_ligne + this->nb_noeud -2);
            ij i_R2(nm_ligne + nb_comp, 2*nm_ligne + this->nb_noeud - 1);
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_R1_, 1));
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_R2, 1));
            /** Kirchhoff's first law (nodal rule) */
            if (2*nb_comp + noeud1 < nb_ligne){     /** row of noeud1 */
                ij i_1(2*nb_comp + noeud1 , 2*nm_ligne + this->nb_noeud - 2);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_1, 1));
            }
            if (2*nb_comp + noeud2 < nb_ligne){
                ij i_2(2*nb_comp + noeud2 , 2*nm_ligne + this->nb_noeud - 1);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_2, 1));
            }
        }
        
        if ((*itthis)->type() == "C"){              /** if component is CAPACITOR, its nodes and parameters are taken */
            nm_ligne++;
            noeud1 = (*itthis)->noeuds().front();   /** the node number is the column in the matrix */
            noeud2 = (*itthis)->noeuds().back();
            param = (*itthis)->param().front();
            ij C_n1(nm_ligne, noeud1 - 1);
            ij C_n2(nm_ligne, noeud2 - 1);
            this->systeme.insert(std::pair<ij,std::complex<double> >(C_n1, -param*std::complex<double>(0.0,1.0)*omega));
            this->systeme.insert(std::pair<ij,std::complex<double> >(C_n2, param*std::complex<double>(0.0,1.0)*omega));
            ij i_C1(nm_ligne, 2*nm_ligne + this->nb_noeud -2);
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_C1, -1)); // !?
            /** component current */
            ij i_C1_(nm_ligne + nb_comp, 2*nm_ligne + this->nb_noeud -2);
            ij i_C2(nm_ligne + nb_comp, 2*nm_ligne + this->nb_noeud - 1);
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_C1_, 1));
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_C2, 1));
            /** Kirchhoff's first law (nodal rule) */
            if (2*nb_comp + noeud1 < nb_ligne){  /** row of noeud1 */
                ij i_1(2*nb_comp + noeud1 , 2*nm_ligne + this->nb_noeud - 2);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_1, 1));
            }
            if (2*nb_comp + noeud2 < nb_ligne){
                ij i_2(2*nb_comp + noeud2 , 2*nm_ligne + this->nb_noeud - 1);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_2, 1));
            }
        }
        
        if ((*itthis)->type() == "I"){                /**< if component is CURRENT SOURCE, its nodes and parameters are taken */
            nm_ligne++;
            noeud1 = (*itthis)->noeuds().front();    /** the node number is the column in the matrix */
            noeud2 = (*itthis)->noeuds().back();
            param = (*itthis)->param().front();
            /** Kirchhoff's second law (voltage law) */
            ij I_n1(nm_ligne, noeud1 - 1);
            ij I_n2(nm_ligne, noeud2 - 1);
            this->systeme.insert(std::pair<ij,std::complex<double> >(I_n1, -1));
            this->systeme.insert(std::pair<ij,std::complex<double> >(I_n2, 1));
            ij i_I1(nm_ligne, 2*nm_ligne + this->nb_noeud -2);
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_I1, -param));
            /** component current */
            ij i_I1_(nm_ligne + nb_comp, 2*nm_ligne + this->nb_noeud -2);
            ij i_I2(nm_ligne + nb_comp, 2*nm_ligne + this->nb_noeud - 1);
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_I1_, 1));
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_I2, 1));
            /** Kirchhoff's first law (nodal rule) */
            if (2*nb_comp + noeud1 < nb_ligne){     /** row of noeud1 */
                ij i_1(2*nb_comp + noeud1 , 2*nm_ligne + this->nb_noeud - 2);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_1, 1));
            }
            if (2*nb_comp + noeud2 < nb_ligne){
                ij i_2(2*nb_comp + noeud2 , 2*nm_ligne + this->nb_noeud - 1);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_2, 1));
            }
        }
        if ((*itthis)->type() == "SW"){              /**< if component is SWITCH, its nodes and parameters are taken */
            nm_ligne++;
            noeud1 = (*itthis)->noeuds().front();    /** the node number is the column in the matrix */
            noeud2 = (*itthis)->noeuds().back();
            param = (*itthis)->param().front();
            /** Kirchhoff's second law (voltage law) */
            ij SW_n1(nm_ligne, noeud1 - 1);
            ij SW_n2(nm_ligne, noeud2 - 1);
            this->systeme.insert(std::pair<ij,std::complex<double> >(SW_n1, -1));
            this->systeme.insert(std::pair<ij,std::complex<double> >(SW_n2, 1));
            ij i_SW1(nm_ligne, 2*nm_ligne + this->nb_noeud -2);
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_SW1, -param));
            /** component current */
            ij i_SW1_(nm_ligne + nb_comp, 2*nm_ligne + this->nb_noeud -2);
            ij i_SW2(nm_ligne + nb_comp, 2*nm_ligne + this->nb_noeud - 1);
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_SW1_, 1));
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_SW2, 1));
            /** Kirchhoff's first law (nodal rule) */
            if (2*nb_comp + noeud1 < nb_ligne){     /** row of noeud1 */
                ij i_1(2*nb_comp + noeud1 , 2*nm_ligne + this->nb_noeud - 2);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_1, 1));
            }
            if (2*nb_comp + noeud2 < nb_ligne){
                ij i_2(2*nb_comp + noeud2 , 2*nm_ligne + this->nb_noeud - 1);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_2, 1));
            }
        }
        if ((*itthis)->type() == "K"){
            nm_ligne++;
            int noeud3,noeud4;
            std::list<int>l_noeud;  /** creat a new list l */
            l_noeud = (*itthis)->noeuds();
            noeud1 = l_noeud.front();    /** the node number is the column in the matrix */
            l_noeud.pop_front();
            noeud2 = l_noeud.front();
            std::cout << "noeud2 =" << noeud2 << std::endl;
             l_noeud.pop_front();
            noeud3 = l_noeud.front();
            std::cout << "noeud3 =" << noeud3 << std::endl;
            noeud4 =  l_noeud.back();
            std::list<std::complex<double> >l_param; 
            l_param = (*itthis)->param();
            std::complex<double> L1, L2, M;
            L1 = l_param.front();
            l_param.pop_front();
            L2 = l_param.front();
            M = l_param.back();
             /** Kirchhoff's second law (voltage law) */
            ij K_n1(nm_ligne, noeud1 - 1);
            ij K_n2(nm_ligne, noeud2 - 1);
            ij K_n3(nm_ligne, noeud3 - 1);
            ij K_n4(nm_ligne, noeud4 - 1);
            this->systeme.insert(std::pair<ij,std::complex<double> >(K_n1, -L2));
            this->systeme.insert(std::pair<ij,std::complex<double> >(K_n2, L2));
            this->systeme.insert(std::pair<ij,std::complex<double> >(K_n3, M));
            this->systeme.insert(std::pair<ij,std::complex<double> >(K_n4, -M));
            /**  L2(V1-V2) - M(V4-V3) - (L1L2-M^2)*j*omega*i_K1 = 0 */
            ij i_K1(nm_ligne, 2*nm_ligne + this->nb_noeud -2);
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_K1, (M*M - L1*L2)*std::complex<double>(0.0,1.0)*omega));
             /** component current */
            ij i_K1_(nm_ligne + nb_comp, 2*nm_ligne + this->nb_noeud -2);
            ij i_K2_(nm_ligne + nb_comp, 2*nm_ligne + this->nb_noeud - 1);
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_K1_, 1));
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_K2_, 1));
             /** Kirchhoff's first law (nodal rule) */
            if (2*nb_comp + noeud1 < nb_ligne){     /** row of noeud1 */
                ij i_1(2*nb_comp + noeud1 , 2*nm_ligne + this->nb_noeud - 2);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_1, 1));
            }
            if (2*nb_comp + noeud2 < nb_ligne){
                ij i_2(2*nb_comp + noeud2 , 2*nm_ligne + this->nb_noeud - 1);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_2, 1));
                // 
                ij i_G1(2*nb_comp + noeud2 , 13);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_G1, 1));
            }
            /** increment a row */
            nm_ligne++;
            /** Kirchhoff's second law (voltage law) */
            ij K_n1_(nm_ligne, noeud1 - 1);
            ij K_n2_(nm_ligne, noeud2 - 1);
            ij K_n3_(nm_ligne, noeud3 - 1);
            ij K_n4_(nm_ligne, noeud4 - 1);
            this->systeme.insert(std::pair<ij,std::complex<double> >(K_n1_, -M));
            this->systeme.insert(std::pair<ij,std::complex<double> >(K_n2_, M));
            this->systeme.insert(std::pair<ij,std::complex<double> >(K_n3_, L1));
            this->systeme.insert(std::pair<ij,std::complex<double> >(K_n4_, -L1));
            /**  M(V1-V2) - L1(V4-V3) - (M^2-L1L2)*j*omega*i_K3 = 0 */
            ij i_K3(nm_ligne, 2*nm_ligne + this->nb_noeud -2);
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_K3, (L1*L2 - M*M)*std::complex<double>(0.0,1.0)*omega));
             /** component current */
            ij i_K3_(nm_ligne + nb_comp, 2*nm_ligne + this->nb_noeud -2);
            ij i_K4_(nm_ligne + nb_comp, 2*nm_ligne + this->nb_noeud - 1);
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_K3_, 1));
            this->systeme.insert(std::pair<ij,std::complex<double> >(i_K4_, 1));
            if (2*nb_comp + noeud3 < nb_ligne){     /** row of noeud1 */
                ij i_3(2*nb_comp + noeud3 , 2*nm_ligne + this->nb_noeud - 2);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_3, 1));
            }
            if (2*nb_comp + noeud4 < nb_ligne){
                ij i_4(2*nb_comp + noeud4 , 2*nm_ligne + this->nb_noeud - 1);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_4, 1));
                //
                ij i_G5(2*nb_comp + noeud4 , 14);
                this->systeme.insert(std::pair<ij,std::complex<double> >(i_G5, 1));
            }
        }
    }
    }
}

/** \brief display the complex admittance matrix connecting current and potential phasers */
void circuit::afficheSysteme(){
    
    std::cout << "ICI, affichage de Systeme :)" << std::endl;
    std::cout << "- - - - - - - - - - " << std::endl;
    std::map<ij,std::complex<double> >::iterator its;
    /** browse of the system matrix*/
    for (its = this->systeme.begin(); its != this->systeme.end(); its++){      /**< browse of the system matrix*/
        ij I;
        I = its->first;
        std::cout << I << its->second << std::endl;
    }
}
/** \brief build the system right hand side */
void circuit::setRhs(){
    std::list<Nports*>::iterator itthis;        /** iterator points to this */
    std::list<Nports*>::const_reverse_iterator itM;
    itM = this->liste_compo.rbegin();
    int nb_comp = this->nb_comp;
    if ((*itM)->type() == "M"){                 /** if earthing is in list, 0 is added to the vector rhs */
        this->rhs.push_back(0);
        this->liste_compo.pop_back();           /** earthing is removed from the list */
        nb_comp-= 1;
    }
    std::list<Nports*>::iterator itK;
    for (auto itK = this->liste_compo.begin(); itK != this->liste_compo.end(); itK++){
        /** if MUTUAL INDUCTANCE is in the list of component */ 
        if ((*itK)->type() == "K"){
            nb_comp = (this->nb_comp - 1)*2 + 6 + this->nb_noeud;
        }
    } 
    /** browsing the component list */
    int nb_ligne = 2*nb_comp + this->nb_noeud;
    for (itthis = this->liste_compo.begin(); itthis != this->liste_compo.end(); itthis++){
        if ((*itthis)->type() == "Vs"){         /** if there is a voltage source, its E parameter is added to the vector rhs */
            std::complex<double> E;
            std::complex<double> Omega;
            Omega = (*itthis)->param().back();
            E = (*itthis)->param().front();
            this->rhs.push_back(E);
            
        }
        else{
            this->rhs.push_back(0);
        }
    }
    /** adding M to the component list (previously removed) */
    for (int i = 0; i < nb_ligne - nb_comp - 1; i++){
        this->rhs.push_back(0);
    }
}

void circuit::afficheRhs(){
    std::cout << "Ici, affichage de Rhs :) " << std::endl;
    std::cout << "- - - - - - - - - - " << std::endl;
    std::vector<std::complex<double> >::iterator itr;
    for (itr = this->rhs.begin(); itr != this->rhs.end(); itr++){
        std::cout << (*itr) << std::endl;
    }
}


void circuit::matVect(std::vector<std::complex<double> >*vect, std::vector<std::complex<double> >*res){
    /** (vect,res) with vect,res two 1D complex vectors */
    std::map<ij,std::complex<double> >::iterator itM;       /**< sparse matrix iterator */
    int cptLigne = 0;
    itM = this->systeme.begin();
    std::complex<double> S = 0;
    while (itM != this->systeme.end()){
        ij I = itM->first;
        if (I.geti() == cptLigne){                          /**< same row */
            int j = I.getj();
            S+=itM->second*(*vect)[j];                      /**< result */
            itM++;
            ij I_ = itM->first;           // le suivant de I
            if ( itM == this->systeme.end() ){              /**< next iteration */
                (*res)[I.geti()] = S;
            }
            if ( itM != this->systeme.end() && I.geti() != I_.geti()){   /**< the next one is not on the same row as I */
                (*res)[I.geti()] = S;
                if (I.geti() - I_.geti() > 1){            /**< next row is null */
                    int cpt = I_.geti();
                    while (cpt != I.geti()) {
                        (*res)[I.geti()] = 0;;
                        cptLigne++;
                        cpt++;
                    }
                }
                S = 0;
                cptLigne++;
            }
        }
    }
}

void circuit::clVect(std::complex<double> a, std::vector<std::complex<double> >* X, std::complex<double> b, std::vector<std::complex<double> >* Y, std::vector<std::complex<double> >* res){
    for (int i = 0; i < X->size(); i++){
        std::complex<double> r = a*(*X)[i] + b*(*Y)[i];     /**< r = aX + bY with a,b complex scalars and X,Y two 1D complex vectors */
        (*res)[i] = r ;
    }
}

std::complex<double> circuit::prodScalair(std::vector<std::complex<double> > *X, std::vector<std::complex<double> > *Y){
    std::complex<double> res = 0;
    for (int i = 0; i < X->size(); i++){
        res+=(*X)[i] * (*Y)[i];                          /**< res = (X,Y ), classic scalar product */
    }
    return res;
}

void circuit::cl_vectDevect(std::complex<double> a, std::vector<std::vector<std::complex<double> > >*X, std::complex<double> b, std::vector<std::vector<std::complex<double> > >*Y, int colX, int colY){
    
    for (int i = 0; i < X->size(); i++){  // parcourir la ligne
        (*X)[i][colX] = a*(*X)[i][colX] + b*(*Y)[i][colY];  /**< aX + bY with a,b complex scalars and X,Y two 2D complex vectors */
    }
}

void circuit::cl_vect_vectDevect(std::complex<double> a, std::vector<std::complex<double> > *X, std::complex<double> b, std::vector<std::vector<std::complex<double> > > *Y, int colY){
    
    for (int i = 0; i < X->size(); i++){
        (*X)[i] = a*(*X)[i] + b*(*Y)[i][colY];
    }
}

void circuit::matvectDevect(std::vector<std::vector<std::complex<double> > > *X, std::vector<std::complex<double> > *res, int colX){
    std::vector<std::complex<double> >*tmp = new std::vector<std::complex<double> >(res->size());
    for (int i = 0; i < res->size(); i++){
        (*tmp)[i] = (*X)[i][colX];           /**< tmp gets X column  i line */
    }
    matVect(tmp, res);
}

std::complex<double> circuit::prodvectDevect(std::vector<std::vector<std::complex<double> > >*X, std::vector<std::vector<std::complex<double> > >*Y, int col){
    /** (X,Y) with X,Y two 2D complex vectors */
    std::vector<std::complex<double> >*tmpX = new std::vector<std::complex<double> >(X->size());
    std::vector<std::complex<double> >*tmpY = new std::vector<std::complex<double> >(X->size());
    for (int i = 0; i < X->size(); i++){
        (*tmpX)[i] = (*X)[i][col];           /**< gets X column */
       (*tmpY)[i] = (*Y)[i][col];           /**< gets Y column */
    }
    return prodScalair(tmpX, tmpY);         /**< scalar product */
}


std::complex<double> circuit::prod_vect_vectDevect(std::vector<std::complex<double> >*X, std::vector<std::vector<std::complex<double> > >*Y, int colY){
    /** (X,Y) with X a 1D complex vector and Y a 2D complex vectors */
    std::vector<std::complex<double> >*tmpY = new std::vector<std::complex<double> >(X->size());
    for (int i = 0; i < X->size(); i++){
        (*tmpY)[i] = (*Y)[i][colY];          /**< gets Y column */
    }
    return prodScalair(X, tmpY);
}

std::vector<std::complex<double> >* circuit::conjugue(std::vector<std::vector<std::complex<double> > >*X, int colX){
    
   std::vector<std::complex<double> >*tmp = new std::vector<std::complex<double> >(X->size());
    
    for (int i = 0; i < X->size(); i++){
        std::complex<double> I = (*X)[i][colX];   /**< gets each element of X */
        (*tmp)[i] = conj(I);                      /**< gets the conjugate of each element */
    }
    return tmp;
}


void circuit::copie(std::vector<std::vector<std::complex<double> > > *X, std::vector<std::complex<double> > *Y, int colX){
    
    for (int i = 0; i < Y->size(); i++){
        (*X)[i][colX] = (*Y)[i];        /**< gets X column */
    }
}

void circuit::affichageVect(std::vector<std::complex<double> >v ){
    std::cout << " Affichage de vecteur " << std::endl;
    for (int i = 0; i < v.size(); i++){
        std::cout << v[i] << std::endl;     /**< display a 1D complex vector */
    }
}


void circuit::solve(){
    int N;
    N = (this->rhs).size();             /**< the number of iterations of the algorithm is the rhs size */
    /**< initialization of necessary vetcors and 2D vectors  >*/
    std::vector<std::vector<std::complex<double> > >*d = new std::vector<std::vector<std::complex<double> > >(N,std::vector<std::complex<double> >(N+1));
    std::vector<std::vector<std::complex<double> > >*Ad = new std::vector<std::vector<std::complex<double> > >(N,std::vector<std::complex<double> >(N+1));
    std::vector<std::complex<double> >*AdAd = new std::vector<std::complex<double> >(N);
    std::vector<std::complex<double> >*y = new std::vector<std::complex<double> >(N);
    std::vector<std::complex<double> >*r = new std::vector<std::complex<double> >(N);
    std::vector<std::complex<double> >*Ay = new std::vector<std::complex<double> >(N);
    std::vector<std::complex<double> >*Z = new std::vector<std::complex<double> >(N);
    std::vector<std::complex<double> >*conjAd = new std::vector<std::complex<double> >(N);
    
    /** Test of fonction solve, compare with with vector x on matlab */
    
    std::vector<std::complex<double> >  F (std::vector<std::complex<double> >(8));
    F[0]=std::complex<double>(1.0, 1.0); F[1]=std::complex<double>(-50.0, -50.0); F[2]=std::complex<double>(-77.0, -77.0);
    F[3]=std::complex<double>(-1.0, -1.0); F[4]=std::complex<double>(2.0, 2.0); F[5]=std::complex<double>(2.0, 2.0);
    F[6]=std::complex<double>(2.0, 2.0); F[7]=std::complex<double>(3.0, 3.0);

    
    std::vector<std::complex<double> >*b = &(this->rhs);
    
    matVect(y, Ay);             /**< Ay = A*y*/
    clVect(1, b, -1, Ay, r);    /**< r = b - Ay */
    copie(d, r, 0);             /**< d(:,0) = r */
    std::vector<std::complex<double> >*Ad0 = new std::vector<std::complex<double> >(N);
    std::complex<double> beta;
    std::complex<double> Ad_z;
    
    matvectDevect(d, Ad0, 0);    /**< Ad0 = A*d(:,0), Ad first <b> column <\b>  */
    copie(Ad, Ad0, 0);           /**< Ad(:,0) = Ad0 */
    conjAd = conjugue(Ad, 0);    /**< Ad(:,0)', conjugate of Ad(:,0) */
    std::complex<double> p;
    p = prod_vect_vectDevect(conjAd, Ad, 0);   /**< p = (Ad,conj(Ad)) */
    (*AdAd)[0] = p;              /**< AdAd(0) = Ad(:,0)'*Ad(:,0); */
    for (int it = 0; it < N; it++){
        std::complex<double> z;
        std::complex<double> alpha;
        conjAd = conjugue(Ad, it);    /**< Ad(;,it)', conjugate of Ad(;,it) */
        z = prodScalair(conjAd, r);   /**< z = Ad(:,it)'*r */
        alpha = z / (*AdAd)[it];
        cl_vect_vectDevect(1, y, alpha, d, it);   /**< y = y + alpha * d(;,it) */
        if (it == N-1){
            for (int t = 0; t < N ; t++){
                std::complex<double> res = (*y)[t];
                this->sol.push_back(res);
            }
        }
        
        cl_vect_vectDevect(1, r, -alpha, Ad, it);   /**< r = r - alpha * Ad(;,it) */
        copie(d, r, it + 1);        /**< d(;,it+1) = r; */
        matVect(r, Z);              /**< Z = A*r */
        copie(Ad, Z, it + 1);       /**< Ad(;, it+1) = Z */
        for (int j = 0; j <= it ; j++){
            conjAd = conjugue(Ad, j);
            Ad_z = prodScalair(conjAd, Z);   /**< Ad_z = (Ad(:,j)'*z) */
            beta = - Ad_z / (*AdAd)[j];      /**< beta = -(Ad(:,j)'*z) / AdAd(j,1) */
            cl_vectDevect(1, Ad, beta, Ad, it + 1, j);  /**< Ad(:,it+1)=Ad(:,it+1)+beta*Ad(:,j) */
            cl_vectDevect(1, d, beta, d, it + 1, j);    /**< d(:,it+1)=d(:,it+1)+beta*d(:,j) */
        }
        conjAd = conjugue(Ad, it + 1);       /**<conjugate of AD(;,it+1) */
        (*AdAd)[it+1] = prod_vect_vectDevect(conjAd, Ad, it + 1);  /**<AdAd(;,it+1)=conjugate of  AD(;,it+1)*Ad */
    }
    std::cout << "Affichage de sol " << std::endl;
    affichageVect(this->sol);
}

