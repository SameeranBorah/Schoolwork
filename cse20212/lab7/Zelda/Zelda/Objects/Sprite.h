//
//  Sprite.h
//  Zelda
//
//  Copyright (c) 2014 John Lake. All rights reserved.

#ifndef __Zelda__Sprite__
#define __Zelda__Sprite__
#include <iostream>
#include "Boundary.h"
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"


class Sprite{

    
public:
        //Constructor & Deconstructor
    Sprite();
    ~Sprite();


        //Size of Sprite
    void setSize(int,int); 
    void setWidth(int);
    void setHeight(int);
    int getWidth();
    int getHeight();

        //If the sprite is alive or not
    void setIsAlive(bool);
    bool isAlive();

        //Location of sprite on SCREEN
    void setScreenLocation(int,int);
    void setXScreenLocation(int);
    void setYScreenLocation(int);
    int getXScreenLocation();
    int getYScreenLocation();

        //Location of the sprite in the LEVEL
    void setCanvasLocation(int,int);
    void setXCanvasLocation(int);
    void setYCanvasLocation(int);
    int getXCanvasLocation();
    int getYCanvasLocation();


        //Velocity of the sprite
    void setXVel(int);
    void setYVel(int);
    void setVel(int,int);
    int getXVel();
    int getYVel();

        //Acceleration of the sprite
    void setXAcc(int);
    void setYAcc(int);
    void setAcc(int,int);
    int getXAcc();
    int getYAcc();
    void updatePosition();
    void undoUpdatePosition();

        //Collision Detection
    void setBounds(int,int,int,int); 
    Boundary getBounds();
    int collidesWith(Sprite);
    int isColliding();
    


        //Loading Textures from files
    void loadBMPForTexture(const char * file);
    void loadIMGForTexture(const char * file);

        //Drawing to the screen:
    void setRenderer(SDL_Renderer *r); 
    void renderSprite();
    void setDest(int,int,int,int);//Set the x,y,w,h of the destination Sprite

        //Flipping of the Sprite
    void setFlip(SDL_RendererFlip);
    SDL_RendererFlip getFlip();


        //Source/Destination Rectangles
    SDL_Rect getSource();
    SDL_Rect getDest();   //Dest will use screen locations
    void setSource(int,int,int,int); //Set the x,y,w,h part of the source file to get the image.

protected:
        //State variables (Location, size, etc.)
    int xScreen;
    int yScreen;
    int xCanvas;
    int yCanvas;
    int xVel;
    int yVel;
    int xAcc;
    int yAcc;
    int width;
    int height;
    bool alive;
    int orientation; //Left/right/up/down/etc
    int colliding;
    Boundary bounds;


        //SDL specific:
    SDL_Rect src; //Where in the spritesheet the sprite comes from
    SDL_Rect dst; //Where on the screen the sprite will go (same as x, y, width, and height.)
    SDL_Renderer *r;   //The Rendering context of the sprite.
    SDL_RendererFlip flip;
    SDL_Texture *tex;  //What the sprite looks like
    };
#endif /* defined(__HeatTransfer__Sprite__) */
