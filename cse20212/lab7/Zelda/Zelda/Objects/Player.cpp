//
//  Player.cpp
//  Zelda
//
//  Created by John Lake on 3/14/14.
//  Copyright (c) 2014 John Lake. All rights reserved.
//

#include "Player.h"
#include <iostream> 
using namespace std;


Player::Player(){currentPlatform = 360;}



    //Increase vertical velocity: lets the user jump.
void Player::jump(){
    if(!hasJumped){
        setVel(getXVel(),-70);
        setAcc(0,10);
        hasJumped = 1;
    }
}


    //Checks if the jump is over.

    //Updates the position of the sprite on the CANVAS
void Player::updatePosition(){
    xScreen += xVel;
    yScreen += yVel;
    xCanvas += xVel;
    yCanvas += yVel;
    xVel+= xAcc;
    yVel += yAcc;
    if(yCanvas > currentPlatform){
        hasJumped = 0;
        yVel = 0;
        yCanvas = currentPlatform;
        yScreen = currentPlatform;
        yAcc = 0; 
    }
    setBounds(xCanvas,yCanvas,xCanvas+width,yCanvas+height);
}

    //Used in collisions, so that a sprite doesn't get stuck in a wall.
void Player::undoUpdatePosition(){
    xScreen -= xVel;
    yScreen -= yVel;
    xCanvas -= xVel;
    yCanvas -= yVel;
    xVel-= xAcc;
    yVel -= yAcc;
    setBounds(xCanvas,yCanvas,xCanvas+width,yCanvas+height);
}
void Player::fall(int g){
    setAcc(getXAcc(),g);
}
int Player::isJumping(){ return hasJumped;}

void Player::setPlatform(int p){
    currentPlatform = p;
}
int Player::getPlatform(){
    return currentPlatform;
}

