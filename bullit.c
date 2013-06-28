// *** ADDED BY HEADER FIXUP ***
#include <cstdlib>
// *** END ***
#include "bullit.h"
#include "world.h"
#include <cmath>

cBullit::cBullit(cWorld* oWorld, const char* chTileSource, int iSpriteHeight, int iSpriteWidth, int iAngle, int iSpeed) : cLevelObject(oWorld, chTileSource, iSpriteHeight, iSpriteWidth)
{

    X = (oWorld->oPlayerObject->X);
    Y = oWorld->oPlayerObject->Y + (oWorld->oPlayerObject->oGFXLayer->p_Source->iSpriteHeight / 2);

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
    oGFXLayer->p_LevelData[0][0].iIndex=0;

    //Movement
    iScaleX=cos(iAngle);
    iScaleY=sin(iAngle);
    iVelocityX=(iSpeed*iScaleX);
    iVelocityY=(iSpeed*iScaleY);
}

cBullit::~cBullit()
{}

void cBullit::fAI()
{
    X+= iVelocityX;
    Y+= iVelocityY;
}
