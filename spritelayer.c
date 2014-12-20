/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
/** \brief
 *
 * \param
 * \param
 * \return
 * Note: Do always set blOptimize to false when blIsBuffered is true.
 */

#include "spritelayer.h"
#include "world.h"
#include <cstring>
#include <fstream>

using namespace std;

SDL_Surface *spritelayerscreen;

void cSpriteLayer::drawPixel(SDL_Surface *screen, int x, int y, Uint8 r, Uint8 g, Uint8 b) {
    Uint32 color = SDL_MapRGB(screen->format, r, g, b);
    switch (screen->format->BytesPerPixel) {
    case 1: { // 8-bpp
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
        *bufp = color;
    }
    break;
    case 2: { // 15-bpp or 16-bpp
        Uint16 *bufp;
        bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
        *bufp = color;
    }
    break;
    case 3: { // 24-bpp mode, usually not used
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3;
        if(SDL_BYTEORDER == SDL_LIL_ENDIAN) {
            bufp[0] = color;
            bufp[1] = color >> 8;
            bufp[2] = color >> 16;
        } else {
            bufp[2] = color;
            bufp[1] = color >> 8;
            bufp[0] = color >> 16;
        }
    }
    break;
    case 4: { // 32-bpp
        Uint32 *bufp;
        bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
        *bufp = color;
    }
    break;
    }
}


bool cSpriteLayer::pixelIsTransparant(int row, int col, int x, int y, int colcount){

    // Find out while tile this is.. in the sprite source.

    //Get the start TopLeft position.
    int rowinsource = leveldata[row][col].row;
    int colinsource = leveldata[row][col].index;

    //Get the pixel
    int pixely = rowToYInSpriteSheet(rowinsource) + y;
    int pixelx = colToXInSpriteSheet(colinsource) + x;

    bool solid = (bool)source->pixelinfo[pixelx][pixely].transparant;

    if(solid){
        drawPixel(world->screensurface, x + (colcount * world->levellayer->source->spritewidth),y,0,255,0);
    }else{
        drawPixel(world->screensurface, x + (colcount * world->levellayer->source->spritewidth),y,255,0,0);
    }

    Uint8 r, g, b; // temporary
    Uint32 pixelcolor = world->levellayer->source->getPixelColor(world->levellayer->source->bitmap,pixelx,pixely);
    SDL_GetRGB(pixelcolor, world->levellayer->source->bitmap->format, &r,&g,&b);

    drawPixel(world->screensurface, x + (colcount * world->levellayer->source->spritewidth), y+32, r, g, b);

    TRACE("pixelIsTransparant","Row: %d  Col: %d  RowInSource: %d  ColInSource: %d  PixelX: %d  PixelY: %d  iX: %d  iY: %d  Solid: %s", row, col, rowinsource, colinsource, pixelx, pixely, x ,y, solid ? "true" : "false");

    return solid;

}

cSpriteLayer::cSpriteLayer(cWorld* _world, int rows, int cols, int spriteheight, int spritewidth, bool optimize, bool isbuffered, bool usecolorkey, int keyr, int keyg, int keyb) {
    world = _world;

    /**< Initialize variables and setup data object holding the level data */
    initLayer(rows, cols, spriteheight, spritewidth, optimize, isbuffered);

    /**< Setup (source) object that contains the Sprite Sheet. */
    if(usebuffer) {
        buffer = SDL_CreateRGBSurface(SDL_HWSURFACE,(cols*spritewidth),(rows*spriteheight),
                                        world->screensurface->format->BitsPerPixel,
                                        world->screensurface->format->Rmask,
                                        world->screensurface->format->Gmask,
                                        world->screensurface->format->Bmask,
                                        world->screensurface->format->Amask);

        source = new cSprite(world, buffer);
    } else {
        source = new cSprite(world);
    }

    /**< Commmit the Color key for all surfaces. */
    if(usecolorkey) {
        colorkeyr = keyr;
        colorkeyg = keyg;
        colorkeyb = keyb;
        if(usebuffer) {
            SDL_SetColorKey(buffer, SDL_SRCCOLORKEY, SDL_MapRGB(buffer->format, colorkeyr, colorkeyg, colorkeyb));
        }
        source->setColorKey(colorkeyr, colorkeyg, colorkeyb);
    }

    /**< Fill map data with init data */
    initMap();
}

void cSpriteLayer::getSlopes() {
    source->getSlopes();
}

void cSpriteLayer::clearlayer() {
    SDL_Rect rect;
    Uint32 color;
    if(usebuffer) {
        color = SDL_MapRGB (buffer->format, 0, 0, 0);
        SDL_FillRect (buffer, NULL, color);
    } else {
        color = SDL_MapRGB (world->screensurface->format, 0, 0, 0);
        SDL_FillRect (world->screensurface, NULL, color);
    }

}


void cSpriteLayer::initLayer(int rows, int cols, int _spriteheight, int _spritewidth, bool optimize, bool isbuffered) {
    spriteheight = _spriteheight;
    spritewidth = _spritewidth;
    x = 0;
    y = 0;
    rowcount = rows;
    colcount = cols;
    colorkeyr = 0;
    colorkeyg = 0;
    colorkeyb = 0;
    optmizelayer = optimize;
    usebuffer = isbuffered;

    //create data object
    leveldata = new slevelblock*[rows];
    for(int i=0; i < rows; i++)
        leveldata[i] = new slevelblock[cols];
}

void cSpriteLayer::setSpriteHeight(int pixels) {
    spriteheight = pixels;
}

int cSpriteLayer::getSpriteHeight() {
    return spriteheight;
}

void cSpriteLayer::setSpriteWidth(int pixels) {
    spritewidth = pixels;
}

int cSpriteLayer::getSpriteWidth() {
    return spritewidth;
}

Uint8 cSpriteLayer::returnSpriteFlags(int row, int col) {
    return leveldata[row][col].flags;
}

void cSpriteLayer::initMap() {
    for (int row = 0; row < rowcount; row++) {
        for (int col = 0; col < colcount; col++) {
            leveldata[row][col].index = 1;
            leveldata[row][col].row = 1;
            leveldata[row][col].type = EMPTY;
            leveldata[row][col].flags = (unsigned char)~(PLATFORM | DAMAGE);
        }
    }
}

cSpriteLayer::~cSpriteLayer() {
    SDL_FreeSurface(spritelayerscreen);
    SDL_FreeSurface(buffer);
}

SDL_Surface* cSpriteLayer::render(signed int camx, signed int camy) {
    // Don't draw things that are outside the view.
    int startcol=0;
    int startrow=0;
    int endcol=colcount;
    int endrow=rowcount;


    if(optmizelayer) {
        startcol = xToCol(-camx);
        endcol = xToCol((-camx)+world->config->screenwidth);
        startrow = yToRow(-camy);
        endrow = yToRow((-camy)+world->config->screenheight);

        // Protect drawing level outside its boundaries
        if(startcol<0) {
            startcol=0;
        }
        if(startrow<0) {
            startrow=0;
        }
        if(endcol>colcount) {
            endcol=colcount;
        }
        if(endrow>rowcount) {
            endrow=rowcount;
        }
    }

    // Loop
    for (int row = startrow; row < endrow; row++) {
        for (int col = startcol; col < endcol; col++) {
            if(leveldata[row][col].type != EMPTY)
                source->render(leveldata[row][col].index, leveldata[row][col].row, (colToX(col)+camx)+x, (rowToY(row)+camy)+y);
        }
    }

}

SDL_Surface* cSpriteLayer::getBufferSurface() {
    return buffer;
}
int cSpriteLayer::getTotalRows() {
    return rowcount;
}
int cSpriteLayer::getTotalCols() {
    return colcount;
}

signed int cSpriteLayer::colToXInSpriteSheet(signed int col) {
    return (col*(spritewidth+source->spritespacer)) + source->spritespacer; // See below
}
signed int cSpriteLayer::rowToYInSpriteSheet(signed int row) {
    TRACE("pixelIsTransparant","iSpriteHeightOffset: %d",source->spriteheightoffset);
    return source->spriteheightoffset + (row*(source->spriteheight+source->spritespacer)); //TODO: The last value (iSpriteSpace isnt correct, it should be heightoffset, but somehow it doesnt work)
}

signed int cSpriteLayer::colToX(signed int col) {
    return (col*spritewidth);
}
signed int cSpriteLayer::rowToY(signed int row) {
    return (row*spriteheight);
}
signed int cSpriteLayer::xToCol(signed int width) {
    return (width/spritewidth);
}
signed int cSpriteLayer::yToRow(signed int height) {
    return (height/spriteheight);
}
signed int cSpriteLayer::getWidth() {
    return colcount * spritewidth;
}
signed int cSpriteLayer::getHeight() {
    return rowcount * spriteheight;
}
bool cSpriteLayer::isBuffered() {
    return usebuffer;
}
