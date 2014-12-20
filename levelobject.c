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

cLevelObject::cLevelObject(cWorld* _world, const char* tilesource, int spriteheight, int spritewidth) {

    // Store references to data objects localy
    world = _world;

    // Init variables
    movespeed=1;
    x=0;
    y=0;
    isalive=true;
}

bool cLevelObject::checkLevelCollision() {
    //TODO: MAYBE THIS FUNCTION IS DEADCODE.. Don't know for sure.

    //Level tile collision + Gravity
    int colstart, colend, rowstart, rowend;

    colstart = world->levellayer->xToCol(gfxlayer->x);
    colend = world->levellayer->xToCol(gfxlayer->x + (gfxlayer->getSpriteWidth()-1));
    rowstart = world->levellayer->yToRow(gfxlayer->y);
    rowend = world->levellayer->yToRow(gfxlayer->y + (gfxlayer->getSpriteHeight()-1));

    bool collide = false;

    for (int row = rowstart ; row <= rowend ; row++ ) {
        for (int col = colstart ; col <= colend ; col++ ) {
            if(!(world->levellayer->leveldata[row][col].type != SPRITE) && ((gfxlayer->y + gfxlayer->getHeight()) < world->config->screenheight)) {
                // collide
                collide = true;
                break;
            }
        }
    }
    return collide;
}

cLevelObject::~cLevelObject() {
}

void cLevelObject::aI() {
    //Implemenet object artificial intelligence here. For example movement automation.
    //Overide this (if needed) in the derived class
}

void cLevelObject::update() {
    aI();

    //Update graphical layer
    gfxlayer->x = x;
    gfxlayer->y = y;
    gfxlayer->render(world->cam->x, world->cam->y);
}

bool cLevelObject::isAlive() {
    return isalive;
}

bool cLevelObject::checkDirectionCollision(cSpriteLayer* object, int direction) {
    return checkDirectionCollision(object, direction, 1);
}

void cLevelObject::getHorScanPos(cSpriteLayer* object, int column, int &begin, int &end) {
    // This function calculates where the object is in the current column, and then
    // return the begin and end pixel in this tile, to rasterscan.
    int objectstartincol = (object->x / world->levellayer->source->spritewidth);
    int objectendincol = ((object->x + object->getWidth()) / world->levellayer->source->spritewidth);
    // There are 3 situations that can occure..
    int alg=0;
    if ((objectstartincol == column)&&(objectendincol != column)) {
        // The begin index of the object IS in this column.
        // The   end index of the object IS NOT in this column.
        alg = 1;
        begin = (object->x % (world->levellayer->source->spritewidth));
        end = world->levellayer->source->spritewidth-1; // -1 because the index is zero based
    } else if((objectstartincol != column)&&(objectendincol == column)) {
        // The begin index of the object IS NOT in this column.
        // The   end index of the object IS in this column.
        alg = 2;
        begin = 0;
        end =  ((object->x + object->getWidth()-1) % world->levellayer->source->spritewidth);
    } else if((objectstartincol != column)&&(objectendincol != column)) {
        // The begin index of the object IS NOT in this column.
        // The   end index of the object IS NOT in this column.
        alg = 3;
        begin = 0;
        end = world->levellayer->source->spritewidth-1;
    } else {
        begin = 0;
        end = 0;
    }

    TRACE("getHorScanPos","Algorithm: %d  StartPX: %d  EndPX: %d", alg, begin, end);
}

void cLevelObject::getPositionInLevel(cSpriteLayer* sourceobject, objpos* position, int& colstart, int& colend, int& rowstart, int& rowend) {
    colstart = world->levellayer->xToCol(position->x);
    colend = world->levellayer->xToCol((position->x + (sourceobject->getSpriteWidth()-1)));
    rowstart = world->levellayer->yToRow(position->y);
    rowend = world->levellayer->yToRow((position->y + (sourceobject->getSpriteHeight()-1))) ;

    TRACE("getPositionInLevel","ObjX: %d  ObjY: %d  newX: %d  newY: %d  height: %d  width: %d  ColS: %d  ColE: %d  RowS: %d  RowE: %d", sourceobject->x, sourceobject->y, position->x, position->y, sourceobject->source->spriteheight, sourceobject->source->spritewidth, colstart, colend, rowstart, rowend);
}

bool cLevelObject::checkDirectionCollision(cSpriteLayer* object, int direction, int pixels) {
    bool collide = false;

    objpos* newpos = new objpos(); //new virtual object position
    newpos->x = object->x;
    newpos->y = object->y;

    switch(direction) {
        case UP:    newpos->y -= pixels;   break;
        case RIGHT: newpos->x += pixels;   break;
        case DOWN:  newpos->y += pixels;   break;
        case LEFT:  newpos->x -= pixels;   break;
    }

    int colstart, colend, rowstart, rowend;
    getPositionInLevel(object,newpos,colstart,colend,rowstart,rowend);

    switch(direction) {
        case UP:
            for (int col = colstart ; col <= colend ; col++ ) {
                if(world->levellayer->leveldata[rowstart][col].type == SPRITE) collide = true;

            }
            break;
        case RIGHT:
            for (int row = rowstart ; row <= rowend ; row++ ) {
                if(world->levellayer->leveldata[row][colend].type == SPRITE) collide = true;
            }
            break;
        case DOWN:
            collide = collideDown(object, newpos, colstart, colend, rowstart, rowend, pixels);
            break;
        case LEFT:
            for (int row = rowstart ; row <= rowend ; row++ ) {
                if(world->levellayer->leveldata[row][colstart].type == SPRITE) collide = true;
            }
            break;
    }

    if(collide)
        TRACE("checkDirectionCollision","COLLIDE! Direction: %d", direction);

    return collide;
}

bool cLevelObject::collideDown(cSpriteLayer* sourceobject, objpos* position, int colstart, int colend, int rowstart, int rowend, int pixels) {
    int colcount;
    bool collide=false;
    for (int col = colstart ; col <= colend ; col++ ) {                         // for each column in this row
        if(world->levellayer->leveldata[rowend][col].type == SPRITE) {     // only scan if this column is a sprite instead of air.
            int pixelstart=0, pixelend=0;
            getHorScanPos(sourceobject, col, pixelstart, pixelend);             // Find the pixel range to scan
            TRACE("checkDirectionCollision","Col: %d  Startpixel: %d  Endpixel:  %d", col, pixelstart, pixelend);

            if(true) {                                                          // Use sloped based detection
                for(int pixel=pixelstart; pixel<pixelend; pixel++) {
                    if(world->levellayer->pixelIsTransparant(rowend, col, pixel, ((position->y + sourceobject->source->spriteheight) % world->levellayer->source->spriteheight) + (pixels-1), colcount)) {
                        collide = true;
                        TRACE("checkDirectionCollision","Depth: %d", ((position->y + sourceobject->source->spriteheight) % world->levellayer->source->spriteheight));
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
