#include "player.h"

cPlayer::cPlayer(SDL_Surface* screen, cSpriteLayer* oLevelLayerRef, cCamera* oCamRef, char* chTileSource, int iSpriteHeight, int iSpriteWidth, int iScreenWidthRef, int iScreenHeightRef) : cLevelObject(screen, oLevelLayerRef, oCamRef, chTileSource, iSpriteHeight, iSpriteWidth, iScreenWidthRef, iScreenHeightRef)
{
    // Init Variables
    fMoveDirection(NONE,false);
    iGravity=1;
    iVelocityY=0;
    iVelocityFall=0;
    iJumpFactor=17;
    blIsJumping=false;
    X=40; //Initial player deployment
    Y=40;
}

cPlayer::~cPlayer()
{}

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
    fMoveByUserInput();
    fGravityPhysics();
    fJumpPhysics();
}

void cPlayer::fGravityPhysics()
{
    // Down wards gravity, dont do this while jumping because jumping has it own gravity physics
    if(!blIsJumping)
    {
        if(!fCheckDirectionCollision(oPlayerLayer,DOWN,iMoveSpeed+iVelocityFall))
        {
            Y+=iMoveSpeed+iVelocityFall;
            iVelocityFall++;
        }
        else
        {
            //User has hit something below him
            iVelocityFall=0;
            blIsJumping=false;
        }
    }
}

void cPlayer::fMoveByUserInput()
{
    if(blMoveRight)
        if(!fCheckDirectionCollision(oPlayerLayer,RIGHT))
        {
            X+= iMoveSpeed;
            oPlayerLayer->p_LevelData[0][0].iIndex=1; //Todo: do this better
        }

    if(blMoveLeft)
        if(!fCheckDirectionCollision(oPlayerLayer,LEFT))
        {
            X-= iMoveSpeed;
            oPlayerLayer->p_LevelData[0][0].iIndex=0; //Todo: do this better
        }

}

void cPlayer::fJumpPhysics()
{
    if(blIsJumping && (iVelocityY >= -iJumpFactor))
    {
        if(iVelocityY >0) //Going UP
        {
            //Check if there is something above me
            if(fCheckDirectionCollision(oPlayerLayer,UP,iVelocityY))
            {
                //We know that nr (iVelocityY) of pixels there is something above us. But we don't know exactly where that object begins. To avoid that the
                //jump is aborted way below the edge we need to find the exact starting position of the object above us.
                int iRemainingPixels;
                for(iRemainingPixels=1; iRemainingPixels<=iVelocityY; iRemainingPixels++)
                {
                    if(fCheckDirectionCollision(oPlayerLayer,UP,iRemainingPixels))
                    {
                        // We found it, the abvove object's edge is (iRemainingPixels) away from me.
                        break;
                    }
                }

                if(iRemainingPixels==1)
                {
                    //The object is just one pixel above me, we dont have to interpolate
                    iVelocityY=0;
                }
                else
                {
                    //The object is multiple pixels away, set the iVelocity to the Remaining pixels. So next time we hit this function the
                    //collision detection is done with this amount of pixels.
                    iVelocityY = iRemainingPixels;
                }
            }
        }
        else
        {
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
    }
    else
    {
        iVelocityY=0;
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
