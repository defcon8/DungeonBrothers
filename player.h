#include "levelobject.h"

class cPlayer : public cLevelObject
{
  private:

  public:
    cPlayer(SDL_Surface* screen, cSpriteLayer* oLevelLayerRef, cCamera* oCamRef, char* chTileSource, int iSpriteHeight, int iSpriteWidth, int iScreenWidthRef, int iScreenHeightRef);
    ~cPlayer();
    void fAI();
};


