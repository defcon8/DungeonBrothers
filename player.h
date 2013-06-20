#include "levelobject.h"

class cPlayer : public cLevelObject
{
  private:
    bool blIsJumping;
    int iGravity, iVelocityY, iJumpFactor;


  public:
    bool blMoveUp, blMoveRight, blMoveDown, blMoveLeft;

    cPlayer(SDL_Surface* screen, cSpriteLayer* oLevelLayerRef, cCamera* oCamRef, char* chTileSource, int iSpriteHeight, int iSpriteWidth, int iScreenWidthRef, int iScreenHeightRef);
    ~cPlayer();
    void fAI();
    void fMoveDirection(int iDirection, bool blEnabled);
    void fJump();
};


