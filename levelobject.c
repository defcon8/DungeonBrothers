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
    //TODO: MAYBE THIS FUNCTION IS DEADCODE.. Don't know for sure.

    //Level tile collision + Gravity
    int iColStart, iColEnd, iRowStart, iRowEnd;

    iColStart=oWorld->oLevelLayer->fXToCol(oGFXLayer->x);
    iColEnd=oWorld->oLevelLayer->fXToCol(oGFXLayer->x + (oGFXLayer->fGetSpriteWidth()-1));
    iRowStart=oWorld->oLevelLayer->fYToRow(oGFXLayer->y);
    iRowEnd=oWorld->oLevelLayer->fYToRow(oGFXLayer->y + (oGFXLayer->fGetSpriteHeight()-1));

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

cLevelObject::~cLevelObject() {
}

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

void cLevelObject::getHorScanPos(cSpriteLayer* p_object, int column, int &begin, int &end) {
    // This function calculates where the object is in the current column, and then
    // return the begin and end pixel in this tile, to rasterscan.
    int objectStartInCol = (p_object->x / oWorld->oLevelLayer->p_Source->iSpriteWidth);
    int objectEndInCol = ((p_object->x + p_object->fGetWidth()) / oWorld->oLevelLayer->p_Source->iSpriteWidth);
    // There are 3 situations that can occure..
    int alg=0;
    if ((objectStartInCol == column)&&(objectEndInCol != column)) {
        // The begin index of the object IS in this column.
        // The   end index of the object IS NOT in this column.
        alg = 1;
        begin = (p_object->x % (oWorld->oLevelLayer->p_Source->iSpriteWidth));
        end = oWorld->oLevelLayer->p_Source->iSpriteWidth-1; // -1 because the index is zero based
    } else if((objectStartInCol != column)&&(objectEndInCol == column)) {
        // The begin index of the object IS NOT in this column.
        // The   end index of the object IS in this column.
        alg = 2;
        begin = 0;
        end =  ((p_object->x + p_object->fGetWidth()-1) % oWorld->oLevelLayer->p_Source->iSpriteWidth);
    } else if((objectStartInCol != column)&&(objectEndInCol != column)) {
        // The begin index of the object IS NOT in this column.
        // The   end index of the object IS NOT in this column.
        alg = 3;
        begin = 0;
        end = oWorld->oLevelLayer->p_Source->iSpriteWidth-1;
    } else {
        begin = 0;
        end = 0;
    }

    TRACE("getHorScanPos","Algorithm: %d  StartPX: %d  EndPX: %d",alg,begin,end);
}

void cLevelObject::getPositionInLevel(cSpriteLayer* sourceobject, objPos* position, int& iColStart, int& iColEnd, int& iRowStart, int& iRowEnd) {
    iColStart=oWorld->oLevelLayer->fXToCol(position->x);
    iColEnd=oWorld->oLevelLayer->fXToCol((position->x + (sourceobject->fGetSpriteWidth()-1)));
    iRowStart=oWorld->oLevelLayer->fYToRow(position->y);
    iRowEnd=oWorld->oLevelLayer->fYToRow((position->y + (sourceobject->fGetSpriteHeight()-1))) ;

    TRACE("getPositionInLevel","ObjX: %d  ObjY: %d  newX: %d  newY: %d  height: %d  width: %d  ColS: %d  ColE: %d  RowS: %d  RowE: %d", sourceobject->x, sourceobject->y, position->x, position->y, sourceobject->p_Source->iSpriteHeight, sourceobject->p_Source->iSpriteWidth, iColStart, iColEnd, iRowStart, iRowEnd);
}

bool cLevelObject::fCheckDirectionCollision(cSpriteLayer* oObject, int iDirection, int iAmountOfPixels) {
    bool blCollide = false;

    objPos* newPos = new objPos(); //new virtual object position
    newPos->x = oObject->x;
    newPos->y = oObject->y;

    switch(iDirection) {
        case UP:    newPos->y -= iAmountOfPixels;   break;
        case RIGHT: newPos->x += iAmountOfPixels;   break;
        case DOWN:  newPos->y += iAmountOfPixels;   break;
        case LEFT:  newPos->x -= iAmountOfPixels;   break;
    }

    int iColStart, iColEnd, iRowStart, iRowEnd;
    getPositionInLevel(oObject,newPos,iColStart,iColEnd,iRowStart,iRowEnd);

    switch(iDirection) {
        case UP:
            for (int iCol = iColStart ; iCol <= iColEnd ; iCol++ ) {
                if(oWorld->oLevelLayer->p_LevelData[iRowStart][iCol].iType == SPRITE) blCollide = true;

            }
            break;
        case RIGHT:
            for (int iRow = iRowStart ; iRow <= iRowEnd ; iRow++ ) {
                if(oWorld->oLevelLayer->p_LevelData[iRow][iColEnd].iType == SPRITE) blCollide = true;
            }
            break;
        case DOWN:
            blCollide = collideDown(oObject, newPos, iColStart, iColEnd, iRowStart, iRowEnd, iAmountOfPixels);
            break;
        case LEFT:
            for (int iRow = iRowStart ; iRow <= iRowEnd ; iRow++ ) {
                if(oWorld->oLevelLayer->p_LevelData[iRow][iColStart].iType == SPRITE) blCollide = true;
            }
            break;
    }

    if(blCollide)
        TRACE("fCheckDirectionCollision","COLLIDE! Direction: %d", iDirection);

    return blCollide;
}

bool cLevelObject::collideDown(cSpriteLayer* sourceobject, objPos* position, int colstart, int colend, int rowstart, int rowend, int amountofpixels) {
    int colcount;
    bool collide=false;
    for (int col = colstart ; col <= colend ; col++ ) {                         // for each column in this row
        if(oWorld->oLevelLayer->p_LevelData[rowend][col].iType == SPRITE) {     // only scan if this column is a sprite instead of air.
            int pixelstart=0, pixelend=0;
            getHorScanPos(sourceobject, col, pixelstart, pixelend);             // Find the pixel range to scan
            TRACE("fCheckDirectionCollision","Col: %d  Startpixel: %d  Endpixel:  %d", col, pixelstart, pixelend);

            if(true) {                                                          // Use sloped based detection
                for(int pixel=pixelstart; pixel<pixelend; pixel++) {
                    if(oWorld->oLevelLayer->fPixelIsTransparant(rowend, col, pixel, ((position->y + sourceobject->p_Source->iSpriteHeight) % oWorld->oLevelLayer->p_Source->iSpriteHeight) + (amountofpixels-1), colcount)) {
                        collide = true;
                        TRACE("fCheckDirectionCollision","Depth: %d", ((position->y + sourceobject->p_Source->iSpriteHeight) % oWorld->oLevelLayer->p_Source->iSpriteHeight));
                        break; // We don't have to scan furhter once we collide, TURN OFF FOR DEBUGGING, SHOULD BE ON FOR PERFORMANCE
                    }
                }
            } else {
                collide = true;
            }

            if(collide) break; // We don't have to scan furhter once we collide, TURN OFF FOR DEBUGGING, SHOULD BE ON FOR PERFORMANCE
        }
        colcount++;
    }

    return collide;
}
