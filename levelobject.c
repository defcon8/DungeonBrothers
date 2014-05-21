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

void cLevelObject::getHorScanPos(cSpriteLayer* p_object, int column, int &begin, int &end)
{
                // This function calculates where the object is in the current column, and then
                // return the begin and end pixel in this tile, to rasterscan.
                int objectStartInCol = (p_object->x / oWorld->oLevelLayer->p_Source->iSpriteWidth);
                int objectEndInCol = ((p_object->x + p_object->fGetWidth()) / oWorld->oLevelLayer->p_Source->iSpriteWidth);
                // There are 3 situations that can occure..
                if ((objectStartInCol == column)&&(objectEndInCol != column)){
                               // The begin index of the object IS in this column.
                               // The   end index of the object IS NOT in this column.
                               TRACE("getHorScanPos","Algorithm 1");
                               begin = (p_object->x % (oWorld->oLevelLayer->p_Source->iSpriteWidth));
                               end = oWorld->oLevelLayer->p_Source->iSpriteWidth-1; // -1 because the index is zero based
                }else if((objectStartInCol != column)&&(objectEndInCol == column)){
                               // The begin index of the object IS NOT in this column.
                               // The   end index of the object IS in this column.
                               TRACE("getHorScanPos","Algorithm 2");
                               begin = 0;
                               end =  ((p_object->x + p_object->fGetWidth()) % ((oWorld->oLevelLayer->p_Source->iSpriteWidth-1) + oWorld->oLevelLayer->p_Source->iSpriteSpacer))-1;
                }else if((objectStartInCol != column)&&(objectEndInCol != column)){
                               // The begin index of the object IS NOT in this column.
                               // The   end index of the object IS NOT in this column.
                               TRACE("getHorScanPos","Algorithm 3");
                               begin = 0;
                               end = oWorld->oLevelLayer->p_Source->iSpriteWidth-1;
                }else{
                                TRACE("getHorScanPos","Algorithm UNKNOWN - Should not be here!!");
                                begin = 0;
                                end = 0;

                }
}


bool cLevelObject::fCheckDirectionCollision(cSpriteLayer* oObject, int iDirection, int iAmountOfPixels) {
    bool blCollide = false;
    int iNextCol,iNextRow;
    int iColStart, iColEnd, iRowStart, iRowEnd;

    //new virtual object pos
    objPos newPos;
    newPos.x = oObject->x;
    newPos.y = oObject->y;

    switch(iDirection){
    case UP:
        newPos.y -= iAmountOfPixels;
        break;
    case RIGHT:
        newPos.x += iAmountOfPixels;
        break;
    case DOWN:
        newPos.y += iAmountOfPixels;
        break;
    case LEFT:
        newPos.x -= iAmountOfPixels;
        break;

    }

    iColStart=oWorld->oLevelLayer->fXToCol(newPos.x);
    iColEnd=oWorld->oLevelLayer->fXToCol((newPos.x + (oObject->fGetSpriteWidth()-1)));
    iRowStart=oWorld->oLevelLayer->fYToRow(newPos.y);
    iRowEnd=oWorld->oLevelLayer->fYToRow((newPos.y + (oObject->fGetSpriteHeight()-1))) ;

    TRACE("fCheckDirectionCollision","ObjX: %d  ObjY: %d  newX: %d  newY: %d  height: %d  width: %d  ColS: %d  ColE: %d  RowS: %d  RowE: %d",oObject->x, oObject->y, newPos.x, newPos.y, oObject->p_Source->iSpriteHeight,oObject->p_Source->iSpriteWidth,iColStart, iColEnd, iRowStart, iRowEnd);

    switch(iDirection) {
    case UP:
        for (int iCol = iColStart ; iCol <= iColEnd ; iCol++ ) {
            if(oWorld->oLevelLayer->p_LevelData[iRowStart][iCol].iType == SPRITE) {
                blCollide = true;
            }
        }
        break;
    case RIGHT:
        for (int iRow = iRowStart ; iRow <= iRowEnd ; iRow++ ) {
            if(oWorld->oLevelLayer->p_LevelData[iRow][iColEnd].iType == SPRITE) {
                blCollide = true;
            }
        }
        break;
    case DOWN:
        int iColCounter;
        for (int iCol = iColStart ; iCol <= iColEnd ; iCol++ ) {
            // Voor iedere colom op deze rij

            if(oWorld->oLevelLayer->p_LevelData[iRowEnd][iCol].iType == SPRITE){
                // Als het een sprite is, anders doen we sowieso niets

                    // Vind het pixel bereik dat we moeten scannen op transparantie.
                    int iStartPixel=0, iEndPixel=0;
                    getHorScanPos(oObject,iCol,iStartPixel,iEndPixel);
                    //TRACE("fCheckDirectionCollision","Col: %d  Startpixel: %d  Endpixel:  %d",iCol, iStartPixel,iEndPixel);
                    if(true) //use sloped based detection
                    {
                        for(int iPixelInSprite=iStartPixel;iPixelInSprite<iEndPixel;iPixelInSprite++){
                            if(oWorld->oLevelLayer->fPixelIsTransparant(iRowEnd,iCol,iPixelInSprite,((newPos.y + oObject->p_Source->iSpriteHeight) % oWorld->oLevelLayer->p_Source->iSpriteHeight) + (iAmountOfPixels-1),iColCounter))
                            {
                                 blCollide = true;
                                TRACE("fCheckDirectionCollision","Depth: %d", ((newPos.y + oObject->p_Source->iSpriteHeight) % oWorld->oLevelLayer->p_Source->iSpriteHeight));
                                TRACE("fCheckDirectionCollision","ARGGH");
                                //break; // we don't have to scan furhter once we collide, TURNED OFF FOR DEBUGGING, SHOULD BE ON FOR PERFORMANCE
                            }

                        }
                    }else{
                        blCollide = true;
                    }

                    //if(blCollide) // we don't have to scan furhter once we collide, TURNED OFF FOR DEBUGGING, SHOULD BE ON FOR PERFORMANCE
            }
            iColCounter++;
        }
        break;
    case LEFT:
        for (int iRow = iRowStart ; iRow <= iRowEnd ; iRow++ ) {
            if(oWorld->oLevelLayer->p_LevelData[iRow][iColStart].iType == SPRITE) {
                blCollide = true;
            }
        }
        break;
    }


    if(blCollide)
            TRACE("fCheckDirectionCollision","COLLIDE! Direction: %d", iDirection);

    return blCollide;

}
