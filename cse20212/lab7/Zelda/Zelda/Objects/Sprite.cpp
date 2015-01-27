//  Sprite.cpp
//  Class used for storing information about characters/mods on the screen.
//  Stores the textures, locations, and source information.
//  Zelda
//  Copyright (c) 2014 John Lake. All rights reserved.

#include "Sprite.h"
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include <iostream>
#include "Boundary.h"
using namespace std;

Sprite::Sprite(){
    width = 0;
    height = 0;
    alive = false;
    xCanvas = 0;
    yCanvas = 0;
}

Sprite::~Sprite(){
    if(isAlive()){
        alive = false;
        SDL_DestroyTexture(tex);
        IMG_Quit();
    }

}


    //Updates the position of the sprite on the CANVAS
void Sprite::updatePosition(){
    xScreen += xVel;
    yScreen += yVel;
    xCanvas += xVel;
    yCanvas += yVel;
    setBounds(xCanvas,yCanvas,xCanvas+width,yCanvas+height);
    xVel+= xAcc;
    yVel += yAcc;
}

    //Used in collisions, so that a sprite doesn't get stuck in a wall.
void Sprite::undoUpdatePosition(){
    xScreen -= xVel;
    yScreen -= yVel;
    xCanvas -= xVel;
    yCanvas -= yVel;
    setBounds(xCanvas,yCanvas,xCanvas+width,yCanvas+height); 
    xVel-= xAcc;
    yVel -= yAcc;
}

    //Collision detection
Boundary Sprite::getBounds(){
    return bounds;
}
void Sprite::setBounds(int x1, int y1, int x2, int y2){
    bounds.setBounds(x1, y1, x2, y2);
}

    //Checks if a sprite has collided with another sprite.
int Sprite::collidesWith(Sprite other){
    if(bounds.collidesWith(other.getBounds())){
        colliding = 1;
        return 1;
    }
    colliding =0; 
       return 0;

}



    /*
     
     
     DO NOT CHANGE THESE METHODS.  THEY WORK FINE.
     
     
     */


    //Gets BMP files:
void Sprite::loadBMPForTexture(const char * file){
    SDL_Surface *sfc = nullptr;
    sfc = SDL_LoadBMP(file);
    tex = SDL_CreateTextureFromSurface(r, sfc);
    SDL_FreeSurface(sfc);
}

    //Gets other types of files:
void Sprite::loadIMGForTexture(const char *file){
    tex = IMG_LoadTexture(r, file);
}

void Sprite::setRenderer(SDL_Renderer *rend){
    (*this).r = rend;
}
    //Render to the screen at location x,y, with the width/height set
void Sprite::renderSprite(){
    setDest(getXScreenLocation(),getYScreenLocation(),getWidth(),getHeight());
    SDL_Rect dest = getDest();
    SDL_Rect source = getSource();
    SDL_RenderCopyEx(r,tex, &source, &dest, 0, NULL, flip);

}

    //Get/Set the size of the sprite
int Sprite::getWidth(){ return width;}
int Sprite::getHeight(){ return height;}
void Sprite::setSize(int w, int h){
    width = w;
    height = h;
    setBounds(getXCanvasLocation(),getYCanvasLocation(),getXCanvasLocation()+w,getYCanvasLocation()+h);
}
void Sprite::setWidth(int w){width = w;}
void Sprite::setHeight(int h){height = h;}

    //Get and set the location of the sprite on the screen:
int Sprite::getXScreenLocation(){return xScreen;}
int Sprite::getYScreenLocation(){return yScreen;}
void Sprite::setScreenLocation(int x, int y){
    (*this).xScreen = x;
    (*this).yScreen = y;
}
void Sprite::setXScreenLocation(int x){(*this).xScreen = x;}
void Sprite::setYScreenLocation(int y){(*this).yScreen = y;}

    //Get and set the location of the sprite in the level:
int Sprite::getXCanvasLocation(){return xCanvas;}
int Sprite::getYCanvasLocation(){return yCanvas;}
void Sprite::setCanvasLocation(int x, int y){
    (*this).xCanvas = x;
    (*this).yCanvas = y;
}
void Sprite::setXCanvasLocation(int x){(*this).xCanvas = x;}
void Sprite::setYCanvasLocation(int y){(*this).yCanvas = y;}


    //Check whether the sprite is alive or not
bool Sprite::isAlive(){return alive;}
void Sprite::setIsAlive(bool b){alive = b;}

    //Get and store info about velocity/acceleration of the sprite:
void Sprite::setXVel(int x){(*this).xVel = x;}
void Sprite::setYVel(int y){(*this).yVel = y;}
void Sprite::setXAcc(int x){(*this).xAcc = x;}
void Sprite::setYAcc(int y){(*this).yAcc = y;}
void Sprite::setVel(int x, int y){
    xVel = x;
    yVel = y;
}
void Sprite::setAcc(int x, int y){
    xAcc = x;
    yAcc = y;
}
int Sprite::getXVel(){return xVel;}
int Sprite::getYVel(){return yVel;}
int Sprite::getXAcc(){return xAcc;}
int Sprite::getYAcc(){return yAcc;}




    //Return the information for the source/destination rectangles.
SDL_Rect Sprite::getSource(){return src;}
SDL_Rect Sprite::getDest(){return dst;}


    //Only way to set the source x,y and width/height
void Sprite::setSource(int xL, int yL, int width, int height){
    src.x = xL;
    src.y = yL;
    src.w = width;
    src.h = height;
}


    //Function to set the destination information.
void Sprite::setDest(int xL, int yL, int width, int height){
    dst.x = xL;
    dst.y = yL;
    dst.w = width;
    dst.h = height;
}


void Sprite::setFlip(SDL_RendererFlip fl){
    flip = fl;
}

SDL_RendererFlip Sprite::getFlip(){
    return flip;
}

int Sprite::isColliding(){ return colliding;}


