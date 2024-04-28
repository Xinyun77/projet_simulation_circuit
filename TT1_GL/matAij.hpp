/**
 * @file matAij.hpp
 * @author
 * @brief matrix class using map containing the coordinates of the non-zero coefficients
 * @date 2022-03-14
 *
 */

#ifndef matAij_hpp
#define matAij_hpp

#include <stdio.h>
#include <map>
#include "ij.hpp"
#include "mat.hpp"
#include <iostream>
#include <vector>

template<class T> class matAij : public mat{
    
protected:
    std::map<ij, T > coef;
   
public:
    matAij(int = 1, int = 1);  // ligne et colonne
    ~matAij();
    matAij(const matAij &other);
    matAij& operator=(const matAij &other);
    
    T& operator()(int i, int j);
    T operator[](ij );
    void affiche();
    matAij transpose();
    void insert(int , int , T ); // permet d'insérer des éléments
    
    friend std::ostream& operator<<(std::ostream & sortie , const matAij & A){
        typename std::map<ij,T>::const_iterator it;
        ij I;
        for(it = A.coef.begin();it != A.coef.end();it++){
            I = it->first;
            
            std::cout << I << "=" << it->second << std::endl;
        }
        return sortie;
    }
    
    matAij  operator+(matAij const &);
    
    matAij operator*(matAij const & );
    
    void solve(std::vector<T>);
    void matVec(std::vector<T>*, std::vector<T>*);
    
};
//matAij operator+(matAij const &a, matAij const &b);

//réutilise ce qui est dans mat
template<class T> matAij<T>::matAij(int row, int colume) : mat(row, colume){
    
}

template<class T> matAij<T>::~matAij(){
    
}

template<class T> matAij<T>::matAij(const matAij &other): mat(other){
    this->coef = other.coef;
}

 template<class T> matAij<T>& matAij<T>::operator=(const matAij &other){
    this->mat::operator=(other); // utilise surcharge de mat
    this->coef = other.coef;
    return (*this);
}

template<class T> T matAij<T>::operator[](ij I){
    typename std::map<ij,T>::iterator it;
    it = this->coef.find(I);
    if(it != this->coef.end()){  //trouvé
        return it->second;
    }
    else{
        return 0.;
    }
}

template<class T> void matAij<T>::insert(int i, int j,T a){
    if (a != 0. && i<this->row && j<this->colum){  // Et i,j sois dans la matrice
        this->coef[ij(i,j)] = a; //!!!! faut vérifier a != 0 !!!!
    }
    
}

/*
template<class T> std::ostream& operator<<(std::ostream & sortie, matAij<T> & A){
    // un itérateur pour parcourire map
    typename std::map<ij,T>::iterator it;
    ij I;
    for(it = A.coef.begin();it != A.coef.end();it++){
        I = it->first;
        
        std::cout << I << "=" << it->second << std::endl;
    }
    return sortie;
}*/

template<class T> matAij<T> matAij<T>::transpose(){
    matAij R(this->colum,this->row);
    ij I;
    typename  std::map<ij,T>::iterator it;
    for(it=this->coef.begin();it!=this->coef.end();it++){
        I = it->first;
        R.coef[I.swap()] = it->second;
    }
    return R;
}


template<class T> matAij<T> matAij<T>::operator+(matAij<T> const &A){
    //assert(this->row==A.row);
   // assert(this->colum==A.colum);
    matAij R(this->row,this->colum);
    T sum;
    typename  std::map<ij,T>::iterator itthis;
    typename  std::map<ij,T>::const_iterator itA;
    
    T zeros;
    
    
    itA = A.coef.begin();
    itthis=this->coef.begin();
    while ((itA != A.coef.end() && (itthis!=this->coef.end()))){
        if (itA->first==itthis->first){
            sum = itA->second+itthis->second;
            if(sum!=zeros){
                R.coef[itA->first] = sum;
                itA++;
                itthis++;
            }
            
            else if (itA->first < itthis->first){
                R.coef[itA->first] = itA->second;
                itA++;
            }
            else{
                R.coef[itthis->first] = itthis->second;
                itthis++;
            }
        }
        if(itA!=A.coef.end()){
            while (itA != A.coef.end()) {
                R.coef[itA->first] = itA->second;
                itA++;
            }
        }
        if(itthis!=A.coef.end()){
            while (itthis != A.coef.end()) {
                R.coef[itthis->first] = itthis->second;
                itthis++;
            }
        }
    }
    return R;
}


template<class T> void matAij<T>::solve(std::vector<T> b){
    int i,j;
    int m = 100;
    std::vector<std::vector<T> > x(this->row);
    std::vector<std::vector<T> > d(m,std::vector<T>(this->row));
    // vect de taille m * this->row
    d[i][j] = T(0);
    
}


template<class T> void matAij<T>::matVec(std::vector<T>* vect, std::vector<T>* res){
    std::vector<T> y;
    // parcourir la map<ij,T> y[it->first.get()] =  ...
    T S = 0;
    ij I;
    int cptLigne = 0;
    typename  std::map<ij,T>::iterator it;
    it=this->coef.begin();
    while (it!=this->coef.end()){
        I = it->first;
        if (I.geti() == cptLigne){
            int j = I.getj();
            S+=it->second*(*vect)[j];
            it++;
            ij I_ = it->first;
            if (it == this->coef.end()){
                (*res)[I.geti()] = S;
            }
            if (it != this->coef.end() && I.geti() != I_.geti()){
                (*res)[I.geti()] = S;
                if (I.geti() - I_.geti() > 1){  // La ligne suivant s'annule
                    int cpt = I_.geti();
                    while (cpt != I.geti()) {
                        (*res)[I.geti()] = 0;
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





#endif /* matAij_hpp */
