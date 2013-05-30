/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
#include "player.h"

cPlayer::cPlayer(SDL_Surface* screen, cSpriteLayer* oLevelLayerRef, char* chTileSource, int iSpriteHeight, int iSpriteWidth, int iScreenWidthRef, int iScreenHeightRef)
{
      //Start Player Layer
    int iLevelRows=1;
    int iLevelCols=1;
    // 15 (rows) x 20 (cols) of 32px sprites (640x480)

    oLevelLayer = oLevelLayerRef;
    iScreenHeight = iScreenHeightRef;
    iScreenWidth = iScreenWidthRef;


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
    oPlayerLayer->p_LevelData[0][0].iIndex=0;
}

bool cPlayer::fCheckLevelCollision()
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
/**< Returns if the surface is a buffered or not. */
    return blCollide;
}


cPlayer::~cPlayer()
{
}

void cPlayer::fUpdate()
{

    // Init
    iPlayerSpeed=1;


    //Do player movement
    switch(iPlayerDirection)
    {
    case UP:
        if(!fCheckDirectionCollision(oPlayerLayer,UP))
            oPlayerLayer->y-= iPlayerSpeed;
        break;
    case RIGHT:
        if(!fCheckDirectionCollision(oPlayerLayer,RIGHT))
            oPlayerLayer->x+= iPlayerSpeed;
        break;
    case DOWN:
        if(!fCheckDirectionCollision(oPlayerLayer,DOWN))
            oPlayerLayer->y+= iPlayerSpeed;
        break;
    case LEFT:
        if(!fCheckDirectionCollision(oPlayerLayer,LEFT))
            oPlayerLayer->x-= iPlayerSpeed;
        break;
    }

}

bool cPlayer::fCheckDirectionCollision(cSpriteLayer* oObject, int iDirection)
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
