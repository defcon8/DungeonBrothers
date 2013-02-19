#include <SDL/SDL.h>

class cSprite {         
  
  private:
          int iSpriteWidth, iSpriteHeight, iSpriteWidthOffset ,iSpriteHeightOffset, iSpriteSpacer;
          int iColorKeyR, iColorKeyG, iColorKeyB;
          int iScrollOffset;
  
          SDL_Surface* bitmap;
          SDL_Surface *spritescreen;
  
  public:
 
         void fLoad(const char *file);
         void fRender(int iCol, int iRow, int iDestX, int iDestY);
         void fSetSpriteWidth(int iPixels);
         void fSetSpriteHeight(int iPixels);
         void fSetSpriteWidthOffset(int iPixels);
         void fSetSpriteHeightOffset(int iPixels);
         void fSetSpriteSpacer(int iPixels);
         void fSetColorKey(int iR, int iG, int iB);
         void fScroll(int iPixelOffset);
 
    cSprite(SDL_Surface *screen);
    ~cSprite();
    
};
