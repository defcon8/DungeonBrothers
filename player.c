// *** ADDED BY HEADER FIXUP ***
#include <cstdlib>
// *** END ***
#include "player.h"
#include "bullit.h"
#include "world.h"

cPlayer::cPlayer(cWorld* world, char* tilesource, int spriteheight, int spritewidth) : cLevelObject(world, tilesource, spriteheight, spritewidth) {
    // Init Variables
    moveDirection(NONE,false);
    facedirection=LEFT;
    gravity=1;
    velocityy=0;
    velocityx=0;
    velocityfall=0;
    jumprange=12;
    jumpstep=0;
    isjumping=false;
    x=40; //Initial player deployment
    y=40;

    //Setup Layer
    gfxlayer = new cSpriteLayer(world,1,1,spriteheight,spritewidth,false,false,true,0,0,0);

    //Setup Source
    gfxlayer->source->spritespacer = 0;
    gfxlayer->source->setColorKey(0,0,0);
    gfxlayer->source->load(tilesource);
    gfxlayer->source->spritewidthoffset = 0;
    gfxlayer->source->spriteheightoffset = 0;
    gfxlayer->source->spriteheight = spriteheight;
    gfxlayer->source->spritewidth = spritewidth;

    //choose player sprite
    gfxlayer->leveldata[0][0].type=SPRITE;
    gfxlayer->leveldata[0][0].row=0;
    gfxlayer->leveldata[0][0].index=1;

}

cPlayer::~cPlayer() {
}

void cPlayer::setSprite() {
    switch(facedirection) {
    case LEFT:
        gfxlayer->leveldata[0][0].index=0;
        break;

    case RIGHT:
        gfxlayer->leveldata[0][0].index=1;
        break;
    }
}

void cPlayer::jump() {
    if(!isjumping) {
        //iVelocityY=iJumpFactor;
        jumpstep=jumprange;
        isjumping=true;
    }
}

void cPlayer::fire() {
    cBullit* bullit;
    int angle;
    switch(facedirection) {
    case RIGHT:
        angle=0;
        break;

    case LEFT:
        angle=180;
        break;
    }
    bullit= new cBullit(world, "bullit.bmp",10,10,angle,10);


    world->levelobjects.push_back(bullit);    //Add to level object list
}

void cPlayer::aI() {
    moveByUserInput();
    setSprite();
    gravityPhysics();
    jumpPhysics();
}

void cPlayer::gravityPhysics() {
    // Down wards gravity, dont do this while jumping because jumping has it own gravity physics
    if(jumpstep == 0) {
        TRACE("Gravity","Speed: %d", movespeed+velocityfall);
        if(!checkDirectionCollision(gfxlayer,DOWN,movespeed+velocityfall)) {
            y+=movespeed+velocityfall;
            if(velocityfall<4) velocityfall++;
        } else {
            //User has hit something below him
            velocityfall=0;
            isjumping = false;
        }
    }
}

void cPlayer::moveByUserInput() {
    //normal Walk / move operations
    if(moveright) {
        if(!checkDirectionCollision(gfxlayer, RIGHT, movespeed+velocityx)) {
            x += movespeed + velocityx;
            if(velocityx < 2) velocityx++;
            lastdirection = RIGHT;
            facedirection = RIGHT;
        } else {
            velocityx = 0;
        }
    }

    if(moveleft) {
        if(!checkDirectionCollision(gfxlayer, LEFT, movespeed+velocityx)) {
            x -= movespeed + velocityx;
            if(velocityx < 2) velocityx++;
            lastdirection = LEFT;
            facedirection = LEFT;
        } else {
            velocityx = 0;
        }
    }

}

void cPlayer::jumpPhysics() {
    if(isjumping) {
        if(jumpstep>0) {
            jumpstep--;
            if(!checkDirectionCollision(gfxlayer,UP,jumpstep)) {
                y-=jumpstep;
            }
        }
    }
}

void cPlayer::moveDirection(int direction, bool enabled) {
    switch(direction) {
    case NONE:
        moveup = false;
        moveright = false;
        movedown = false;
        moveleft = false;
        break;
    case UP:
        moveup = enabled;
        break;
    case RIGHT:
        moveright = enabled;
        break;
    case DOWN:
        movedown = enabled;
        break;
    case LEFT:
        moveleft = enabled;
        break;
    }
}
