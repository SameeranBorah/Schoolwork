//
//  AnimatedSprite.h
//  Zelda
//
//  Copyright (c) 2014 John Lake. All rights reserved.
//

#ifndef __Zelda__AnimatedSprite__
#define __Zelda__AnimatedSprite__

#include <iostream>
#include "Sprite.h"
#include "AnimatedSprite.h"
class AnimatedSprite : public Sprite{
public:
    AnimatedSprite(); 
    void setNumFrames(int);
    void updateFrame();
    int getSpriteRow();
    void setSpriteRow(int);
    int getNumFrames();
private:
        //Animation Variables:
    int numFrames;
    int frame;
    int spriteRow;

};

#endif /* defined(__HeatTransfer__AnimatedSprite__) */
