#include <SDL/SDL.h>

#include "spritelayer.h"

class cGame {         
  
  private:
    bool blDone;
    bool blEditMode;
    bool blSpritePalet;
    int CamX, CamY;
    int MouseX, MouseY;
  
     
    cSpriteLayer* oLevelLayer;
    cSpriteLayer* oPlayerLayer;
    cSprite* oBackgroundLayer;
  
    void fInitialize();
    void fInitVariables();
    void fLoadObjects();
    void fEvents();
    void fNormalModeEvents();
    void fEditModeEvents();
    void fGameLoop();
    void fRender();
    void fCleanUp();
    void fSave();
    void fDrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B);
    void fRenderEditMode();
    void fDrawRectangle(int x, int y, int w, int h, Uint32 color);
     
    /* The screen surface */
    SDL_Surface *screen;
    
    cSpriteLayer *p_SpriteLayers;
  
  public:
    void Start();
    cGame();
    ~cGame();
    
};
