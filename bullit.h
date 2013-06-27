#ifndef BULLIT_H
#define BULLIT_H
#include "levelobject.h"

using namespace std;

class cWorld;

class cBullit : public cLevelObject
{
  private:

  public:
    cBullit(cWorld* oWorld, char* chTileSource, int iSpriteHeight, int iSpriteWidth);
    ~cBullit();
    void fAI();
};

#endif // PLAYER_H

