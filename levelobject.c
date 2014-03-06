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
#include "world.h"

cLevelObject::cLevelObject(cWorld* oWorldRef, const char* chTileSource, int iSpriteHeight, int iSpriteWidth) {

    // Store references to data objects localy
    oWorld = oWorldRef;

    // Init variables
    iMoveSpeed=1;
    X=0;
    Y=0;
    blIsAlive=true;

}

bool cLevelObject::fCheckLevelCollision() {
    //Level tile collision + Gravity
    int iColStart, iColEnd, iRowStart, iRowEnd;

    iColStart=oWorld->oLevelLayer->fWidthToCol(oGFXLayer->x);
    iColEnd=oWorld->oLevelLayer->fWidthToCol((oGFXLayer->x + oGFXLayer->fGetSpriteWidth()));
    iRowStart=oWorld->oLevelLayer->fHeightToRow(oGFXLayer->y);
    iRowEnd=oWorld->oLevelLayer->fHeightToRow((oGFXLayer->y + oGFXLayer->fGetSpriteHeight()));

    bool blCollide = false;

    for (int iRow = iRowStart ; iRow <= iRowEnd ; iRow++ ) {
        for (int iCol = iColStart ; iCol <= iColEnd ; iCol++ ) {
            if(!(oWorld->oLevelLayer->p_LevelData[iRow][iCol].iType != SPRITE) && ((oGFXLayer->y + oGFXLayer->fGetHeight()) < oWorld->oConfig->m_iScreenHeight)) {
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

void cLevelObject::fAI() {
    //Implemenet object artificial intelligence here. For example movement automation.
    //Overide this (if needed) in the derived class
}

void cLevelObject::fUpdate() {
    fAI();

    //Update graphical layer
    oGFXLayer->x = X;
    oGFXLayer->y = Y;
    oGFXLayer->fRender(oWorld->oCam->X,oWorld->oCam->Y);
}

bool cLevelObject::fIsAlive() {
    return blIsAlive;
}

bool cLevelObject::fCheckDirectionCollision(cSpriteLayer* oObject, int iDirection) {
    return fCheckDirectionCollision(oObject,iDirection,1);
}

bool cLevelObject::fCheckDirectionCollision(cSpriteLayer* oObject, int iDirection, int iAmountOfPixels) {
    bool blCollide = false;
    int iNextCol,iNextRow;
    int iColStart, iColEnd, iRowStart, iRowEnd;
    iColStart=oWorld->oLevelLayer->fWidthToCol(oObject->x+1);
    iColEnd=oWorld->oLevelLayer->fWidthToCol((oObject->x + oObject->fGetSpriteWidth()-1));
    iRowStart=oWorld->oLevelLayer->fHeightToRow(oObject->y+1);
    iRowEnd=oWorld->oLevelLayer->fHeightToRow((oObject->y + oObject->fGetSpriteHeight()-1));

    switch(iDirection) {
    case UP:
        iNextRow=oWorld->oLevelLayer->fHeightToRow(oObject->y - (iAmountOfPixels-1));
        for (int iCol = iColStart ; iCol <= iColEnd ; iCol++ ) {
            if(oWorld->oLevelLayer->p_LevelData[iNextRow][iCol].iType == SPRITE) {
                blCollide = true;
            }
        }
        break;
    case RIGHT:
        iNextCol=oWorld->oLevelLayer->fWidthToCol((oObject->x + oObject->fGetSpriteWidth() + (iAmountOfPixels-1)));
        for (int iRow = iRowStart ; iRow <= iRowEnd ; iRow++ ) {
            if(oWorld->oLevelLayer->p_LevelData[iRow][iNextCol].iType == SPRITE) {
                blCollide = true;
            }
        }
        break;
    case DOWN:
        iNextRow=oWorld->oLevelLayer->fHeightToRow((oObject->y + oObject->fGetSpriteHeight() + (iAmountOfPixels-1)));
        for (int iCol = iColStart ; iCol <= iColEnd ; iCol++ ) {
            if(oWorld->oLevelLayer->p_LevelData[iNextRow][iCol].iType == SPRITE) {
                blCollide = true;
            }
        }
        break;
    case LEFT:
        iNextCol=oWorld->oLevelLayer->fWidthToCol(oObject->x-iAmountOfPixels);
        for (int iRow = iRowStart ; iRow <= iRowEnd ; iRow++ ) {
            if(oWorld->oLevelLayer->p_LevelData[iRow][iNextCol].iType == SPRITE) {
                blCollide = true;
            }
        }
        break;
    }

    return blCollide;

}
