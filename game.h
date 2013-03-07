/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with DevC++ on Win32.
  2013
  
  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
#include <SDL/SDL.h>
#include "spritelayer.h"

class cGame {             
  // Camera Movement    
  #define UP 1
  #define RIGHT 2
  #define DOWN 3
  #define LEFT 4
  #define NONE 0  
  
  private:
    bool blDone;
    bool blEditMode;
    bool blSpritePalet;
    int CamX, CamY;
    int MouseX, MouseY;
    int iCamDirection;
  
     
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
    void fCameraMovement();
    
    int fGetTileCol(int iX, int iTileWidth);
    int fGetTileRow(int iY, int iTileHeight);
     
    /* The screen surface */
    SDL_Surface *screen;
    cSpriteLayer *p_SpriteLayers;
  
  public:
    void Start();
    cGame();
    ~cGame();
    
};
