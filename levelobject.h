/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/

#ifndef LEVELOBJECT_H_
#define LEVELOBJECT_H_

#include <SDL/SDL.h>
#include "spritelayer.h"
#include "camera.h"
#include "ilevelobject.h"

class cWorld;

class cLevelObject : public iLevelObject {

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
#define NONE 0

private:
    bool fCheckLevelCollision();
    void getHorScanPos(cSpriteLayer* p_object, int column, int &begin, int &end);
    struct objPos{
        int x,y;
    };

public:
    //Object Pointers
    cWorld* oWorld;
    cSpriteLayer* oGFXLayer;
    int X,Y;

    cLevelObject(cWorld* oWorldRef, const char* chTileSource, int iSpriteHeight, int iSpriteWidth);
    virtual ~cLevelObject();
    virtual void fUpdate();
    virtual bool fIsAlive();
    virtual void fAI();
    bool fCheckDirectionCollision(cSpriteLayer* oObject, int iDirection);
    bool fCheckDirectionCollision(cSpriteLayer* oObject, int iDirection, int iAmountOfPixels);
    int iMoveSpeed;
    bool blIsAlive;
};

#endif /* LEVELOBJECT_H_ */
