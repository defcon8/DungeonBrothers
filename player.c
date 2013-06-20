#include "player.h"

cPlayer::cPlayer(SDL_Surface* screen, cSpriteLayer* oLevelLayerRef, cCamera* oCamRef, char* chTileSource, int iSpriteHeight, int iSpriteWidth, int iScreenWidthRef, int iScreenHeightRef) : cLevelObject(screen, oLevelLayerRef, oCamRef, chTileSource, iSpriteHeight, iSpriteWidth, iScreenWidthRef, iScreenHeightRef)
{
        // Init Variables
        fMoveDirection(NONE,false);
        iGravity=1;
        iVelocityY=0;
        iJumpFactor=15;
        blIsJumping=false;
}

cPlayer::~cPlayer()
{
}

void cPlayer::fJump()
{
    if(!blIsJumping)
    {
       iVelocityY=iJumpFactor;
       blIsJumping=true;
    }
}

void cPlayer::fAI()
{

    //Movement
    // - Respond to user Input
    if(blMoveUp)
        if(!fCheckDirectionCollision(oPlayerLayer,UP))
            Y-= iMoveSpeed;

    if(blMoveRight)
        if(!fCheckDirectionCollision(oPlayerLayer,RIGHT))
            X+= iMoveSpeed;

    if(blMoveDown)
        if(!fCheckDirectionCollision(oPlayerLayer,DOWN))
            Y+= iMoveSpeed;

    if(blMoveLeft)
        if(!fCheckDirectionCollision(oPlayerLayer,LEFT))
            X-= iMoveSpeed;

    // - Jump Physics
    if(blIsJumping && (iVelocityY >= -iJumpFactor))
    {
        Y=Y-iVelocityY;
        iVelocityY-=iGravity;
    }else{
        blIsJumping=false;
    }
}

void cPlayer::fMoveDirection(int iDirection, bool blEnabled)
{
    switch(iDirection)
    {
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
