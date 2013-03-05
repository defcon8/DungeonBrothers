/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with DevC++ on Win32.
  2013
  
  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
#include "sprite.h"
class cSpriteLayer {         
  
  //Sprite Types
  #define EMPTY 0
  #define SPRITE  1
  
  //Sprite Flags
  #define WALL 1
  #define ENEMYWALL 2
  #define PLATFORM 4
  #define USELIGHT 8
  #define OVERLAP 16
  #define ANBACK 32
  #define ANFRONT 64
  #define WATER 128
  #define DAMAGE 256
  #define CONVL 512
  #define CONVR 1024
  #define TURN 2048
  #define DESTROYABLE 4096

  private:
  
        struct sLevelBlock {
               Uint8 bySource;
               Uint8 iRow;
               Uint8 iIndex;
               Uint8 iType;
               Uint8 iAnimations;
               Uint8 AniFrameStep;
               Uint8 blCollide;
               Uint8 iFlags;
        };
        
        //Local Members
        int iSpriteWidth, iSpriteHeight;
        int iRowCount, iColCount;

        //Methods
        void fInitMap();
        int fColToWidth(int iCol);
        int fRowToHeight(int iRow);

  public:
    cSpriteLayer(SDL_Surface *screen, int iRows, int iCols, int iSpriteHeightPX, int iSpriteWidthPX);
    ~cSpriteLayer();
    
    //Data Objects
    cSprite *p_Source;
    SDL_Surface* fRender(int CamX, int CamY);
    sLevelBlock **p_LevelData;
    
    //Methods
    Uint8 fReturnSpriteFlags(int iRow, int iCol);
    void fSetSpriteWidth(int iPixels);
    int fGetSpriteWidth();
    void fSetSpriteHeight(int iPixels);
    int fGetSpriteHeight();
    
};
