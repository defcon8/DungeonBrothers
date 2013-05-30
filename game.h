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
#include "spritelayer.h"
#include "pencil.h"
#include "debug.h"
#include "camera.h"
#include <time.h>
#include <list>
#include "levelobject.h"
#include "player.h"
#include "enemy.h"

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

    clock_t cStart, cTime;

    cPencil* oPencil;
    cSpriteLayer* oLevelLayer;
    cSpriteLayer* oSpritePicker;
    cSprite* oBackgroundLayer;

    void fInitialize();
    void fInitVariables(int iScrWidth, int iScrHeight);
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
    void fDrawRectangle(int x, int y, int w, int h, Uint32 color);
    void fObjectMovement();
    void fCameraMovement();

    int fGetTileCol(int iX, int iTileWidth);
    int fGetTileRow(int iY, int iTileHeight);

    /* The screen surface */
    SDL_Surface *screen;
    cSpriteLayer *p_SpriteLayers;
    list<iLevelObject*> lLevelObjects;
    cPlayer* oPlayerObject;
    cCamera* oCam;

  public:
    void Start();
    cGame(int iScrWidth, int iScrHeight);
    ~cGame();

};
