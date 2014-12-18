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
#include "SDL/SDL_mixer.h"
#include "world.h"
#include <time.h>
#include "enemy.h"

using namespace std;

class cGame
{

private:
    bool blDone;
    bool blRenderLevel;
    bool blSpritePalet;
    signed int CamX, CamY;
    int scrollOffSet;
    int MouseX, MouseY;
    double dbMouseCornerWidthPerc;
    int iMouseScrollSpeed;
    int iOptimalFrequency;
    int iElapsedSeconds;
    int iStartTime;
    int iRenderedFrames;
    int iFPS;
    char chFPS[5];

    TTF_Font* ttfFont;
    SDL_Color cGreen;
    SDL_Color cBlack;
    SDL_Rect rFPSLocation;

    void functionTests();
    void fInitialize();
    void fInitVariables();
    void fLoadObjects();
    void fEvents();
    void gameModeEvents(SDL_Event *event);
    void editModeEvents(SDL_Event *event);
    void menuModeEvents(SDL_Event *event);
    void fGameLoop();
    void fRender();
    void fCleanUp();
    void fIntro();
    void fSaveLayer(cSpriteLayer *p_SpriteLayer);
    void fSaveDemo();
    void fDrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B);
    void fRenderEditMode();
    void renderMenuMode();
    void fRenderUI();
    void fDrawRectangle(int x, int y, int w, int h, Uint32 color);
    void fObjectMovement();
    void fUpdateLevelObject(iLevelObject* pLevelObject);
    void fFPS();
    int fGetTileCol(int iX, int iTileWidth);
    int fGetTileRow(int iY, int iTileHeight);

public:
    void Start();
    cWorld* oWorld;
    cGame();
    ~cGame();
};
