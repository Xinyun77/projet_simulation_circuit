//
//  mat.hpp
//  TT1_GL
//
//  Created by Li Xinyun on 14/03/2022.
//


#ifndef mat_hpp
#define mat_hpp

#include <stdio.h>

class mat{
protected:
    int row;
    int colum;
public:
    mat();
    mat(int  x,int  y);
    
    ~mat();
    mat(const mat& other);
    mat& operator=(const mat& other);
    mat transpose();
    mat affiche();
};

#endif /* mat_hpp */

