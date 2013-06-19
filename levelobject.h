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

class cLevelObject : public iLevelObject{

  #define UP 1
  #define RIGHT 2
  #define DOWN 3
  #define LEFT 4
  #define NONE 0

private:
    //Methods
    bool fCheckLevelCollision();
    bool fCheckDirectionCollision(cSpriteLayer* oObject, int iDirection);
    void fMove();

    //Variables
    int iScreenWidth, iScreenHeight;
    int iMoveSpeed;
    bool blMoveUp, blMoveRight, blMoveDown, blMoveLeft;

  public:
    //Object Pointers
    cSpriteLayer* oPlayerLayer;
    cSpriteLayer* oLevelLayer;
    cCamera* oCam;

    cLevelObject(SDL_Surface* screen, cSpriteLayer* oLevelLayerRef, cCamera* oCamRef, char* chTileSource, int iSpriteHeight, int iSpriteWidth, int iScreenWidthRef, int iScreenHeightRef);
    virtual ~cLevelObject();
    virtual void fUpdate();
    void fMoveDirection(int iDirection, bool blEnabled);
    virtual void fAI();

};

#endif /* LEVELOBJECT_H_ */
