/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
#include <SDL/SDL.h>
#include "spritelayer.h"
#include "levelobject.h"

class cPlayer : public iLevelObject{

  #define UP 1
  #define RIGHT 2
  #define DOWN 3
  #define LEFT 4
  #define NONE 0

  private:
    cSpriteLayer* oPlayerLayer;
    cSpriteLayer* oLevelLayer;
    bool fCheckLevelCollision();
    bool fCheckDirectionCollision(cSpriteLayer* oObject, int iDirection);
    int iScreenWidth, iScreenHeight;
    int iPlayerDirection;
    int iPlayerSpeed;

  public:
    cPlayer(SDL_Surface* screen, cSpriteLayer* oLevelLayerRef, char* chTileSource, int iSpriteHeight, int iSpriteWidth, int iScreenWidthRef, int iScreenHeightRef);
    virtual ~cPlayer();
    virtual void fUpdate();

};

