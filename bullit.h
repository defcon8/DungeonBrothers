#ifndef BULLIT_H
#define BULLIT_H
#include "levelobject.h"

using namespace std;

class cWorld;

class cBullit : public cLevelObject
{
  private:
      float iScaleX, iScaleY;
      float iVelocityX, iVelocityY;
      int iAngle, iSpeed;
  public:
    cBullit(cWorld* oWorld, const char* chTileSource, int iSpriteHeight, int iSpriteWidth, int iAngleRef, int iSpeedRef);
    ~cBullit();
    void fAI();
};

#endif // PLAYER_H

