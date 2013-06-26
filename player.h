#ifndef PLAYER_H
#define PLAYER_H
#include <list>
#include "levelobject.h"

using namespace std;

class cWorld;

class cPlayer : public cLevelObject
{
  private:
    int iGravity, iVelocityY, iVelocityX, iVelocityFall, iJumpFactor,iLastDirection;
    void fMoveByUserInput();
    void fJumpPhysics();
    void fGravityPhysics();

  public:
    bool blMoveUp, blMoveRight, blMoveDown, blMoveLeft;
    bool blIsJumping;
    void fAI();
    void fMoveDirection(int iDirection, bool blEnabled);
    void fJump();
    void fFire();
    cPlayer(cWorld* oWorld, char* chTileSource, int iSpriteHeight, int iSpriteWidth);
    ~cPlayer();
};

#endif // PLAYER_H


