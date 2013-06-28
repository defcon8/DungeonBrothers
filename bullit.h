#ifndef BULLIT_H
#define BULLIT_H
#include "levelobject.h"

using namespace std;

class cWorld;

class cBullit : public cLevelObject
{
  private:
      int iScaleX, iScaleY;
      int iVelocityX, iVelocityY;
  public:
    cBullit(cWorld* oWorld, const char* chTileSource, int iSpriteHeight, int iSpriteWidth, int iAngle, int iSpeed);
    ~cBullit();
    void fAI();
};

#endif // PLAYER_H

