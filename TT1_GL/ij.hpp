/**
 * @file ij.cpp
 * @author LI Xinyun
 * @brief Coordinates of matrix elements
 * @date 2022-03-14
 *
 */


#ifndef ij_hpp
#define ij_hpp

#include "mat.hpp"
#include <stdio.h>
#include <iostream>

class ij : public mat{
protected:
    int i,j;
public:
    ij(int = 0, int = 0);
    ~ij();
    ij(const ij &other);
    ij& operator=(const ij &other) ;
    friend inline bool operator<(const ij &ij1, const ij &ij2);
    int geti();
    int getj();
    ij swap();
    friend std::ostream& operator<<(std::ostream & , ij &);
    
    bool estEgale(ij const &other) const;

};
bool operator==(ij const &a, ij const &b) ;

inline bool operator<(const ij &ij1, const ij&ij2){
    if (ij1.i < ij2.i) {
        return  1;
    }
    else{
        if (ij1.i==ij2.i){
            if (ij1.j < ij2.j){
                return 1;
            }
        }
        else{
            return 0;
        }
    }
    return 0;
}

#endif /* ij_hpp */
