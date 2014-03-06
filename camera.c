/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
#include "camera.h"

cCamera::cCamera() {
    iVelocityCam=1;
    up=1;
    right=2;
    down=3;
    left=4;
    none=5;
    X=0;
    Y=0;
    Direction=none;
}

cCamera::~cCamera() {
}

