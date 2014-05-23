// *** ADDED BY HEADER FIXUP ***
#include <cstdlib>
// *** END ***
#include "player.h"
#include "bullit.h"
#include "world.h"

cPlayer::cPlayer(cWorld* oWorld, char* chTileSource, int iSpriteHeight, int iSpriteWidth) : cLevelObject(oWorld, chTileSource, iSpriteHeight, iSpriteWidth) {
    // Init Variables
    fMoveDirection(NONE,false);
    iFaceDirection=LEFT;
    iGravity=1;
    iVelocityY=0;
    iVelocityX=0;
    iVelocityFall=0;
    iJumpFactor=14;
    blIsJumping=false;
    X=40; //Initial player deployment
    Y=40;

    //Setup Layer
    oGFXLayer = new cSpriteLayer(oWorld,1,1,iSpriteHeight,iSpriteWidth,false,false,true,0,0,0);

    //Setup Source
    oGFXLayer->p_Source->iSpriteSpacer = 0;
    oGFXLayer->p_Source->fSetColorKey(0,0,0);
    oGFXLayer->p_Source->fLoad(chTileSource);
    oGFXLayer->p_Source->iSpriteWidthOffset = 0;
    oGFXLayer->p_Source->iSpriteHeightOffset = 0;
    oGFXLayer->p_Source->iSpriteHeight = iSpriteHeight;
    oGFXLayer->p_Source->iSpriteWidth = iSpriteWidth;

    //choose player sprite
    oGFXLayer->p_LevelData[0][0].iType=SPRITE;
    oGFXLayer->p_LevelData[0][0].iRow=0;
    oGFXLayer->p_LevelData[0][0].iIndex=1;

}

cPlayer::~cPlayer() {
}

void cPlayer::fSetSprite() {
    switch(iFaceDirection) {
    case LEFT:
        oGFXLayer->p_LevelData[0][0].iIndex=0;
        break;

    case RIGHT:
        oGFXLayer->p_LevelData[0][0].iIndex=1;
        break;
    }
}

void cPlayer::fJump() {
    if(!blIsJumping) {
        //iVelocityY=iJumpFactor;
        blIsJumping=true;
    }else{
        blIsJumping=false;
    }
}

void cPlayer::fFire() {
    cBullit* oBullit;
    int iAngle;
    switch(iFaceDirection) {
    case RIGHT:
        iAngle=0;
        break;

    case LEFT:
        iAngle=180;
        break;
    }
    oBullit= new cBullit(oWorld, "bullit.bmp",10,10,iAngle,10);


    oWorld->lLevelObjects.push_back(oBullit);    //Add to level object list
}

void cPlayer::fAI() {
    fMoveByUserInput();
    fSetSprite();
    fGravityPhysics();
    fJumpPhysics();
}

void cPlayer::fGravityPhysics() {
    // Down wards gravity, dont do this while jumping because jumping has it own gravity physics
    if(!blIsJumping) {
        TRACE("Gravity","Speed: %d", iMoveSpeed+iVelocityFall);
        if(!fCheckDirectionCollision(oGFXLayer,DOWN,iMoveSpeed+iVelocityFall)) {
            Y+=iMoveSpeed+iVelocityFall;
            if(iVelocityFall<4) iVelocityFall++;
        } else {
            //User has hit something below him
            iVelocityFall=0;
            blIsJumping=false;
        }
    }
}

void cPlayer::fMoveByUserInput() {

    //normal Walk / move operations
    if(blMoveRight)
        if(!fCheckDirectionCollision(oGFXLayer,RIGHT,iMoveSpeed+iVelocityX)) {
            X+= iMoveSpeed+iVelocityX;
            //if(iVelocityX < 2) iVelocityX++;
            iLastDirection=RIGHT;
            iFaceDirection=RIGHT;
        } else {
            iVelocityX=0;
        }

    if(blMoveLeft)
        if(!fCheckDirectionCollision(oGFXLayer,LEFT,iMoveSpeed+iVelocityX)) {
            X-= iMoveSpeed+iVelocityX;
            //if(iVelocityX < 2) iVelocityX++;
            iLastDirection=LEFT;
            iFaceDirection=LEFT;

        } else {
            iVelocityX=0;
        }

    if(blMoveDown)
        if(!fCheckDirectionCollision(oGFXLayer,DOWN,1)) {
            Y+=1;
            //if(iVelocityX < 2) iVelocityX++;
            iLastDirection=DOWN;
        }

    if(blMoveUp)
        if(!fCheckDirectionCollision(oGFXLayer,UP,1)) {
            Y-=1;
            //if(iVelocityX < 2) iVelocityX++;
            iLastDirection=UP;
        }


}

void cPlayer::fJumpPhysics() {
}

void cPlayer::fMoveDirection(int iDirection, bool blEnabled) {
    switch(iDirection) {
    case NONE:
        blMoveUp=false;
        blMoveRight=false;
        blMoveDown=false;
        blMoveLeft=false;
        break;
    case UP:
        blMoveUp=blEnabled;
        break;
    case RIGHT:
        blMoveRight=blEnabled;
        break;
    case DOWN:
        blMoveDown=blEnabled;
        break;
    case LEFT:
        blMoveLeft=blEnabled;
        break;
    }
}
