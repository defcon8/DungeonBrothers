/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "game.h"

#define DEBUG 1

int main (int argc, char *argv[])
{
    MessageBox(NULL, "This is a ALPHA version of Dungeon Brothers. Game is under development.", "Information", MB_OK | MB_ICONINFORMATION);

    cGame* oGame = new cGame(640,480);

    oGame->Start();

    delete oGame;

    return 0;
}
