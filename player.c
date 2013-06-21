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

//  Disabled up, because in this world the user cannot fly ;)
//    if(blMoveUp)
//        if(!fCheckDirectionCollision(oPlayerLayer,UP))
//            Y-= iMoveSpeed;

    if(blMoveRight)
        if(!fCheckDirectionCollision(oPlayerLayer,RIGHT))
            X+= iMoveSpeed;

//  Converted down to a constant gravity
    if(!blIsJumping)
        if(!fCheckDirectionCollision(oPlayerLayer,DOWN))
            Y+= iMoveSpeed;

    if(blMoveLeft)
        if(!fCheckDirectionCollision(oPlayerLayer,LEFT))
            X-= iMoveSpeed;

    // - Jump Physics
    if(blIsJumping && (iVelocityY >= -iJumpFactor))
    {
        if(iVelocityY >0)
        {
            //Going UP
            if(fCheckDirectionCollision(oPlayerLayer,UP))
            {
                //Hit something aboye player
                if(fCheckDirectionCollision(oPlayerLayer,UP,iVelocityY))
                {
                    //Hit something below player
                    iVelocityY=0;
                }
            }
        }else{
            //Going Down
            if(fCheckDirectionCollision(oPlayerLayer,DOWN,abs(iVelocityY)))
            {
                //Hit something below player
                blIsJumping=false;
                iVelocityY=0;
            }
        }

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
