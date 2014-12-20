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
#include <string>
#include "enemy.h"

using namespace std;

class cGame
{

private:
    bool done;
    bool renderlevel;
    bool spritepalet;
    signed int camx, camy;
    int scrolloffset;
    int mousex, mousey;
    double mousecornerwidthperc;
    int mousescrollspeed;
    int optimalfrequency;
    int elapsedseconds;
    int starttime;
    int renderedframes;
    int fps;
    int selectedmenuitem;
    char fpstext[5];
    string menuitems[4];

    TTF_Font* ttffont;
    SDL_Color green;
    SDL_Color yellow;
    SDL_Color black;
    SDL_Rect fpslocation;

    void functionTests();
    void initialize();
    void initVariables();
    void loadObjects();
    void events();
    void gameModeEvents(SDL_Event *event);
    void editModeEvents(SDL_Event *event);
    void menuModeEvents(SDL_Event *event);
    void gameLoop();
    void render();
    void cleanUp();
    void intro();
    void saveLayer(cSpriteLayer *spritelayer);
    void saveDemo();
    void drawPixel(SDL_Surface *screen, int x, int y, Uint8 r, Uint8 g, Uint8 b);
    void renderEditMode();
    void renderMenuMode();
    void renderUI();
    void drawRectangle(int x, int y, int w, int h, Uint32 color);
    void objectMovement();
    void updateLevelObject(iLevelObject* levelobject);
    void calcfps();
    int getTileCol(int x, int tilewidth);
    int getTileRow(int y, int tileheight);

public:
    void start();
    cWorld* world;
    cGame();
    ~cGame();
};
