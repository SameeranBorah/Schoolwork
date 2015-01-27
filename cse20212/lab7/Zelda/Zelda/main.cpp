//
//  main.cpp
//  Zelda
//
//  Created by John Lake on 3/16/14.
//  Copyright (c) 2014 John Lake. All rights reserved.
//

#include <iostream>
#include "SDL2/SDL.h" 
#include "Player.h"
#include "AnimatedSprite.h"
using namespace std;


int main(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *win = nullptr;
    SDL_Event e;
    SDL_Renderer *rend = nullptr;
    win = SDL_CreateWindow("The Legend of Zelda",400,400, 600, 500,SDL_WINDOW_SHOWN);
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    int gameOver = 0;

    AnimatedSprite link;
    link.setSource(0,0,43,49);
    link.setScreenLocation(40,40);
    link.setCanvasLocation(40,40);
    link.setRenderer(rend);
    link.loadIMGForTexture("/Users/johnlake/Documents/Programming/C/CPP/Zelda/Zelda/Sprites/Link.png");
    link.setSize(43,49);
    link.setNumFrames(2);
    link.setSpriteRow(0);

        //y  4   53   102   151   200 249 298
        //x  3   46   89    132   175


    while(!gameOver){
                SDL_RenderClear(rend);
        while(SDL_PollEvent(&e)){
            switch(e.type) {
                case SDL_QUIT:
                    gameOver = 1;
                    break;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){

                        case SDLK_LEFT:
                            link.setXVel(-1);
                            link.setSpriteRow(5);
                            link.setNumFrames(10);
                            break;
                        case SDLK_RIGHT:
                            link.setXVel(1);
                            link.setSpriteRow(7);
                            link.setNumFrames(10);
                            break;
                        case SDLK_UP:
                            link.setYVel(-1);
                            link.setSpriteRow(6);
                            link.setNumFrames(10);
                            break;
                        case SDLK_DOWN:
                            link.setYVel(1);
                            link.setSpriteRow(4);
                            link.setNumFrames(10);

                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch(e.key.keysym.sym){

                        case SDLK_LEFT:
                            if(link.getXVel()<0){
                                link.setXVel(0);
                            }
                            link.setSpriteRow(1);
                            link.setNumFrames(3);
                            break;
                        case SDLK_RIGHT:
                            if(link.getXVel()>0){
                                link.setXVel(0);
                            }
                            link.setSpriteRow(3);
                            link.setNumFrames(3);
                            break;
                        case SDLK_UP:
                            if(link.getYVel()<0){
                                link.setYVel(0);
                            }
                            link.setNumFrames(1);
                            link.setSpriteRow(2);
                            break;
                        case SDLK_DOWN:
                            if(link.getYVel()>0){
                                link.setYVel(0);
                            }
                            link.setSpriteRow(0);
                            link.setNumFrames(3);
                            break;
                    }
                    break;

            }
        }
        cout << link.getSource().y << endl;
        link.updatePosition();
        link.updateFrame();
        link.renderSprite();
        SDL_RenderPresent(rend);
        SDL_Delay(2);
    }

    SDL_Quit();

}

