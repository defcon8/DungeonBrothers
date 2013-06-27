// *** ADDED BY HEADER FIXUP ***
#include <cstdlib>
// *** END ***
#include "player.h"
#include "bullit.h"
#include "world.h"

cPlayer::cPlayer(cWorld* oWorld, char* chTileSource, int iSpriteHeight, int iSpriteWidth) : cLevelObject(oWorld, chTileSource, iSpriteHeight, iSpriteWidth)
{
    // Init Variables
    fMoveDirection(NONE,false);
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

void cPlayer::fFire()
{
     cBullit* oBullit = new cBullit(oWorld, "bullit.bmp",10,10);
     oWorld->lLevelObjects.push_back(oBullit);    //Add to level object list
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
        if(!fCheckDirectionCollision(oGFXLayer,DOWN,iMoveSpeed+iVelocityFall))
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
    //Walk-- slow break down on key up instead of immidiate stop
    if((!blMoveRight && !blMoveLeft) && iVelocityX > 0)
    {
        if(iLastDirection==RIGHT){
                if(fCheckDirectionCollision(oGFXLayer,RIGHT,iVelocityX))
                    X+= iVelocityX;
        }else{
                if(fCheckDirectionCollision(oGFXLayer,LEFT,iVelocityX))
                    X-= iVelocityX;
        }
        iVelocityX--;
    }

    //normal Walk / move operations
    if(blMoveRight)
        if(!fCheckDirectionCollision(oGFXLayer,RIGHT,iMoveSpeed+iVelocityX))
        {
            X+= iMoveSpeed+iVelocityX;
            oGFXLayer->p_LevelData[0][0].iIndex=1; //Set player sprite to other (running left /right) Todo: do this better
            if(iVelocityX < 2) iVelocityX++;
            iLastDirection=RIGHT;
        }else{
            iVelocityX=0;
        }

    if(blMoveLeft)
        if(!fCheckDirectionCollision(oGFXLayer,LEFT,iMoveSpeed+iVelocityX))
        {
            X-= iMoveSpeed+iVelocityX;
            oGFXLayer->p_LevelData[0][0].iIndex=0; //Set player sprite to other (running left /right) Todo: do this better
            if(iVelocityX < 2) iVelocityX++;
            iLastDirection=LEFT;
        }else{
            iVelocityX=0;
        }

}

void cPlayer::fJumpPhysics()
{
    if(blIsJumping && (iVelocityY >= -iJumpFactor))
    {
        if(iVelocityY >0) //Going UP
        {
            //Check if there is something above me
            if(fCheckDirectionCollision(oGFXLayer,UP,iVelocityY))
            {
                //We know that nr (iVelocityY) of pixels there is something above us. But we don't know exactly where that object begins. To avoid that the
                //jump is aborted way below the edge we need to find the exact starting position of the object above us.
                int iRemainingPixels;
                for(iRemainingPixels=1; iRemainingPixels<=iVelocityY; iRemainingPixels++)
                {
                    if(fCheckDirectionCollision(oGFXLayer,UP,iRemainingPixels))
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
            if(fCheckDirectionCollision(oGFXLayer,DOWN,abs(iVelocityY)))
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
