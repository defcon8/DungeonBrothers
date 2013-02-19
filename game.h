#include <SDL/SDL.h>

#include "spritelayer.h"

class cGame {         
  
  private:
    bool blDone;
    bool blEditMode;
    bool blSpritePalet;
    int CamX,CamY;
     
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
     
    /* The screen surface */
    SDL_Surface *screen;
    
    cSpriteLayer *p_SpriteLayers;
  
  public:
    void Start();
    cGame();
    ~cGame();
    
};
