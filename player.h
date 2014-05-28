#ifndef PLAYER_H
#define PLAYER_H
#include <list>
#include "levelobject.h"

using namespace std;

class cWorld;

class cPlayer : public cLevelObject {
private:
    int iGravity, iVelocityY, iVelocityX, iVelocityFall, jumpRange, jumpStep, iLastDirection;
    void fMoveByUserInput();
    void fJumpPhysics();
    void fGravityPhysics();
    void fSetSprite();

public:
    bool blMoveUp, blMoveRight, blMoveDown, blMoveLeft;
    int iFaceDirection;
    bool blIsJumping;
    void fAI();
    void fMoveDirection(int iDirection, bool blEnabled);
    void fJump();
    void fFire();
    cPlayer(cWorld* oWorld, char* chTileSource, int iSpriteHeight, int iSpriteWidth);
    ~cPlayer();
};

#endif // PLAYER_H


