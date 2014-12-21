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
    struct objpos{
        int x,y;
    };
    bool checkLevelCollision();
    void getHorScanPos(cSpriteLayer* p_object, int column, int &begin, int &end);
    void getPositionInLevel(cSpriteLayer* sourceobject, objpos* position, int& colstart, int& colend, int& rowstart, int& rowend);
    bool collideDown(cSpriteLayer* sourceobject, objpos* position, int colstart, int colend, int rowstart, int rowend, int pixels);

public:
    //Object Pointers
    cWorld* world;
    cSpriteLayer* gfxlayer;
    int x,y;

    cLevelObject(cWorld* _world, const char* tilesource, int spriteheight, int spritewidth);
    virtual ~cLevelObject();
    virtual void update();
    virtual bool isAlive();
    virtual void aI();
    bool checkDirectionCollision(cSpriteLayer* object, int direction);
    bool checkDirectionCollision(cSpriteLayer* object, int direction, int pixels);
    int movespeed;
    bool isalive;

};

#endif /* LEVELOBJECT_H_ */
