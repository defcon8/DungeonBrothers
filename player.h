#include "levelobject.h"

class cPlayer : public cLevelObject
{
  private:
    int iGravity, iVelocityY, iVelocityFall, iJumpFactor;
    void fMoveByUserInput();
    void fJumpPhysics();
    void fGravityPhysics();

  public:
    bool blMoveUp, blMoveRight, blMoveDown, blMoveLeft;
    bool blIsJumping;
    cPlayer(SDL_Surface* screen, cSpriteLayer* oLevelLayerRef, cCamera* oCamRef, char* chTileSource, int iSpriteHeight, int iSpriteWidth, int iScreenWidthRef, int iScreenHeightRef);
    ~cPlayer();
    void fAI();
    void fMoveDirection(int iDirection, bool blEnabled);
    void fJump();
};


