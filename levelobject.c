/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
#include "levelobject.h"

cLevelObject::cLevelObject(SDL_Surface* screen, cSpriteLayer* oLevelLayerRef, cCamera* oCamRef, char* chTileSource, int iSpriteHeight, int iSpriteWidth)
{

    // Store references to data objects localy
    oLevelLayer = oLevelLayerRef;
    oCam = oCamRef;


    // Init variables
    iMoveSpeed=1;
    X=0;
    Y=0;

}

bool cLevelObject::fCheckLevelCollision()
{
    //Level tile collision + Gravity
    int iColStart, iColEnd, iRowStart, iRowEnd;

    iColStart=oLevelLayer->fWidthToCol(oGFXLayer->x);
    iColEnd=oLevelLayer->fWidthToCol((oGFXLayer->x + oGFXLayer->fGetSpriteWidth()));
    iRowStart=oLevelLayer->fHeightToRow(oGFXLayer->y);
    iRowEnd=oLevelLayer->fHeightToRow((oGFXLayer->y + oGFXLayer->fGetSpriteHeight()));

    bool blCollide = false;

    for (int iRow = iRowStart ; iRow <= iRowEnd ; iRow++ )
    {
        for (int iCol = iColStart ; iCol <= iColEnd ; iCol++ )
        {
            if(!(oLevelLayer->p_LevelData[iRow][iCol].iType != SPRITE) && ((oGFXLayer->y + oGFXLayer->fGetHeight()) < iScreenHeight))
            {
                // collide
                blCollide = true;
                break;
            }
        }
    }
    return blCollide;
}

cLevelObject::~cLevelObject()
{}

void cLevelObject::fAI()
{
    //Implemenet object artificial intelligence here. For example movement automation.
    //Overide this (if needed) in the derived class
}

void cLevelObject::fUpdate()
{
    fAI();

    //Update graphical layer
    oGFXLayer->x = X;
    oGFXLayer->y = Y;
    oGFXLayer->fRender(oCam->X,oCam->Y);
}

bool cLevelObject::fCheckDirectionCollision(cSpriteLayer* oObject, int iDirection)
{
       return fCheckDirectionCollision(oObject,iDirection,1);
}

bool cLevelObject::fCheckDirectionCollision(cSpriteLayer* oObject, int iDirection, int iAmountOfPixels)
{
       bool blCollide = false;
    int iNextCol,iNextRow;
    int iColStart, iColEnd, iRowStart, iRowEnd;
    iColStart=oLevelLayer->fWidthToCol(oObject->x+1);
    iColEnd=oLevelLayer->fWidthToCol((oObject->x + oObject->fGetSpriteWidth()-1));
    iRowStart=oLevelLayer->fHeightToRow(oObject->y+1);
    iRowEnd=oLevelLayer->fHeightToRow((oObject->y + oObject->fGetSpriteHeight()-1));

    switch(iDirection)
    {
    case UP:
        iNextRow=oLevelLayer->fHeightToRow(oObject->y - (iAmountOfPixels-1));
        for (int iCol = iColStart ; iCol <= iColEnd ; iCol++ )
        {
            if(oLevelLayer->p_LevelData[iNextRow][iCol].iType == SPRITE)
            {
                blCollide = true;
            }
        }
        break;
    case RIGHT:
        iNextCol=oLevelLayer->fWidthToCol((oObject->x + oObject->fGetSpriteWidth() + (iAmountOfPixels-1)));
        for (int iRow = iRowStart ; iRow <= iRowEnd ; iRow++ )
        {
            if(oLevelLayer->p_LevelData[iRow][iNextCol].iType == SPRITE)
            {
                blCollide = true;
            }
        }
        break;
    case DOWN:
        iNextRow=oLevelLayer->fHeightToRow((oObject->y + oObject->fGetSpriteHeight() + (iAmountOfPixels-1)));
        for (int iCol = iColStart ; iCol <= iColEnd ; iCol++ )
        {
            if(oLevelLayer->p_LevelData[iNextRow][iCol].iType == SPRITE)
            {
                blCollide = true;
            }
        }
        break;
    case LEFT:
        iNextCol=oLevelLayer->fWidthToCol(oObject->x-iAmountOfPixels);
        for (int iRow = iRowStart ; iRow <= iRowEnd ; iRow++ )
        {
            if(oLevelLayer->p_LevelData[iRow][iNextCol].iType == SPRITE)
            {
                blCollide = true;
            }
        }
        break;
    }

    return blCollide;

}
