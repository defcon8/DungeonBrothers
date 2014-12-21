/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
#include "..\include\camera.h"
#include "..\include\world.h"

cCamera::cCamera(cWorld* _world)
{
    world = _world;
    velocity=1;
    up=1;
    right=2;
    down=3;
    left=4;
    none=5;
    x=0;
    y=0;
    direction=none;
}

cCamera::~cCamera()
{
}

void cCamera::cameraMovement()
{
    //Do Camera movement
    switch(direction) {
    case 1:
        y += 1;
        break;
    case 2:
        x -= 1;
        break;
    case 3:
        y -= 1;
        break;
    case 4:
        x += 1;
        break;
    }

    if(world->gamemode == MODE_GAME) { // Dont move camera automaticly when in edit mode because we want to move by mouse

        //Let the camera follow the players position. If the camera position is not optimal then increase or decrease the camera position by 1 to have a smooth scrolling effect. Do not follow
        //when the user is jumping..this is kind a hectic.

        //Left/Right
        int pos = -(world->playerobject->x - (world->config->screenwidth/2) - world->playerobject->gfxlayer->getWidth());

        if(pos < x) {
            // Let the Camera go left
            x-=velocity;
        } else if(pos > x) {
            // Let the Camera go left
            x+=velocity;
        }

        //Up/Down
        if(!world->playerobject->isjumping) { //Do not update camera on player jump
            pos = -(world->playerobject->y - (world->config->screenheight/2) - world->playerobject->gfxlayer->getHeight());
            if(pos < y) {
                // Let the Camera go up
                y-=velocity;
            } else if(pos > y) {
                // Let the Camera go down
                y+=velocity;
            } else {
                // The camera is in optimal position
            }
        }

    }
}
