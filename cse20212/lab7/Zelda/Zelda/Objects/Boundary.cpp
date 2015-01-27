//
//  Boundary.cpp
//  Zelda
//
//  Created by John Lake on 3/14/14.
//  Copyright (c) 2014 John Lake. All rights reserved.
//

#include "Boundary.h"

Boundary::Boundary(){x1=0;x2=0;y1=0;y2=0;}
Boundary::Boundary(int x, int y, int z, int w){
    x1=x;
    y1=y;
    x2=z;
    y2=w;
}

int Boundary::collidesWith(Boundary other){
    for(int i = x1; i<= x2;i++){
        for(int j = y1;j<=y2;j++){
            if(i>=other.x1 && i <= other.x2 && j >=other.y1 && j<other.y2){
                return 1;
            }

        }
    }
    return 0;
}

void Boundary::setBounds(int x, int y, int z, int w){
    x1=x;
    y1=y;
    x2=z;
    y2=w;
}
