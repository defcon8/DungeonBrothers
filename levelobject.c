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

cLevelObject::cLevelObject(SDL_Surface* screen, cSpriteLayer* oLevelLayerRef, cCamera* oCamRef, char* chTileSource, int iSpriteHeight, int iSpriteWidth, int iScreenWidthRef, int iScreenHeightRef)
{
    // Init variables
    int iLevelRows=1;
    int iLevelCols=1;
    iMoveSpeed=1;
    fMoveDirection(NONE,false);

    // Store references to data objects localy
    oLevelLayer = oLevelLayerRef;
    iScreenHeight = iScreenHeightRef;
    iScreenWidth = iScreenWidthRef;
    oCam = oCamRef;

    //Setup Layer
    oPlayerLayer = new cSpriteLayer(screen,iLevelRows,iLevelCols,iSpriteHeight,iSpriteWidth,false,iScreenWidth,iScreenHeight,false,false,0,0,0);

    //Setup Source
    oPlayerLayer->p_Source->fSetSpriteSpacer(2);
    oPlayerLayer->p_Source->fLoad(chTileSource);
    oPlayerLayer->p_Source->fSetSpriteWidthOffset(0);
    oPlayerLayer->p_Source->fSetSpriteHeightOffset(0);
    oPlayerLayer->p_Source->fSetSpriteHeight(iSpriteHeight);
    oPlayerLayer->p_Source->fSetSpriteWidth(iSpriteWidth);

    //Setup Player
    oPlayerLayer->p_LevelData[0][0].iType=SPRITE;
    oPlayerLayer->p_LevelData[0][0].iRow=10;
    oPlayerLayer->p_LevelData[0][0].iIndex=2;
}

bool cLevelObject::fCheckLevelCollision()
{
    //Level tile collision + Gravity
    int iColStart, iColEnd, iRowStart, iRowEnd;

    iColStart=oLevelLayer->fWidthToCol(oPlayerLayer->x);
    iColEnd=oLevelLayer->fWidthToCol((oPlayerLayer->x + oPlayerLayer->fGetSpriteWidth()));
    iRowStart=oLevelLayer->fHeightToRow(oPlayerLayer->y);
    iRowEnd=oLevelLayer->fHeightToRow((oPlayerLayer->y + oPlayerLayer->fGetSpriteHeight()));

    bool blCollide = false;

    for (int iRow = iRowStart ; iRow <= iRowEnd ; iRow++ )
    {
        for (int iCol = iColStart ; iCol <= iColEnd ; iCol++ )
        {
            if(!(oLevelLayer->p_LevelData[iRow][iCol].iType != SPRITE) && ((oPlayerLayer->y + oPlayerLayer->fGetHeight()) < iScreenHeight))
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

void cLevelObject::fMoveDirection(int iDirection, bool blEnabled)
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

void cLevelObject::fMove()
{
    //Overide (if needed) by inheretant class
    if(blMoveUp)
        if(!fCheckDirectionCollision(oPlayerLayer,UP))
            oPlayerLayer->y-= iMoveSpeed;

    if(blMoveRight)
        if(!fCheckDirectionCollision(oPlayerLayer,RIGHT))
            oPlayerLayer->x+= iMoveSpeed;

    if(blMoveDown)
        if(!fCheckDirectionCollision(oPlayerLayer,DOWN))
            oPlayerLayer->y+= iMoveSpeed;

    if(blMoveLeft)
        if(!fCheckDirectionCollision(oPlayerLayer,LEFT))
            oPlayerLayer->x-= iMoveSpeed;
}

void cLevelObject::fAI()
{
    //Implemenet object artificial intelligence here. For example enemy movement.
    //Overide this (if needed) in the derived class
}

void cLevelObject::fUpdate()
{
    fAI();
    fMove();
    oPlayerLayer->fRender(oCam->X,oCam->Y);
}

bool cLevelObject::fCheckDirectionCollision(cSpriteLayer* oObject, int iDirection)
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
        iNextRow=oLevelLayer->fHeightToRow(oObject->y -1);
        for (int iCol = iColStart ; iCol <= iColEnd ; iCol++ )
        {
            if(oLevelLayer->p_LevelData[iNextRow][iCol].iType == SPRITE)
            {
                blCollide = true;
            }
        }
        break;
    case RIGHT:
        iNextCol=oLevelLayer->fWidthToCol((oObject->x + oObject->fGetSpriteWidth()));
        for (int iRow = iRowStart ; iRow <= iRowEnd ; iRow++ )
        {
            if(oLevelLayer->p_LevelData[iRow][iNextCol].iType == SPRITE)
            {
                blCollide = true;
            }
        }
        break;
    case DOWN:
        iNextRow=oLevelLayer->fHeightToRow((oObject->y +oObject->fGetSpriteHeight()));
        for (int iCol = iColStart ; iCol <= iColEnd ; iCol++ )
        {
            if(oLevelLayer->p_LevelData[iNextRow][iCol].iType == SPRITE)
            {
                blCollide = true;
            }
        }
        break;
    case LEFT:
        iNextCol=oLevelLayer->fWidthToCol(oObject->x-1);
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