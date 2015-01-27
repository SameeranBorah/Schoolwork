//
//  Boundary.h
//  Used for collision detection in sprites. 
//  Zelda
//
//  Created by John Lake on 3/14/14.
//  Copyright (c) 2014 John Lake. All rights reserved.
//

#ifndef __Zelda__Boundary__
#define __Zelda__Boundary__

#include <iostream>

class Boundary{
public:
    Boundary();
    Boundary(int,int,int,int);
    void setBounds(int,int,int,int); 
    int collidesWith(Boundary); 
private:
    int x1,y1,x2,y2;

};

#endif /* defined(__Snow__Boundary__) */
