/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
#include <SDL/SDL.h>
#include "SDL/SDL_ttf.h"
#include "spritelayer.h"
#include "pencil.h"
#include "player.h"
#include "debug.h"
#include "camera.h"
#include <time.h>
#include <list>
#include "ilevelobject.h"
#include "levelobject.h"
#include "enemy.h"
#include "config.h"

using namespace std;

class cGame {

  private:
    bool blDone;
    bool blEditMode;
    bool blRenderLevel;
    bool blSpritePalet;
    signed int CamX, CamY;
    int MouseX, MouseY;
    int iScreenWidth, iScreenHeight;
    double dbMouseCornerWidthPerc;
    int iMouseScrollSpeed;
    int iOptimalFrequency;
    int iElapsedSeconds;
    int iStartTime;
    int iRenderedFrames;
    int iFPS;

    clock_t cStart, cTime;

    TTF_Font* ttfFont;
    char chFPS[5];
    SDL_Color cRed;
    SDL_Color cBlack;
    SDL_Rect rFPSLocation;

    cConfig* oConfig;
    cPencil* oPencil;
    cSpriteLayer* oLevelLayer;
    cSpriteLayer* oSpritePicker;
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
    void fSaveLayer(cSpriteLayer *p_SpriteLayer);
    void fSaveDemo();
    void fDrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B);
    void fRenderEditMode();
    void fRenderUI();
    void fDrawRectangle(int x, int y, int w, int h, Uint32 color);
    void fObjectMovement();
    void fCameraMovement();
    void fFPS();

    int fGetTileCol(int iX, int iTileWidth);
    int fGetTileRow(int iY, int iTileHeight);

    /* The screen surface */
    SDL_Surface *screen;
    SDL_Surface *textSurface;
    cSpriteLayer *p_SpriteLayers;
    list<iLevelObject*> lLevelObjects;
    cPlayer* oPlayerObject;
    cCamera* oCam;

  public:
    void Start();
    cGame();
    ~cGame();

};
