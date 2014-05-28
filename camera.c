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
#include "world.h"

cCamera::cCamera(cWorld* oWorldRef) {
    oWorld = oWorldRef;
    velocity=1;
    up=1;
    right=2;
    down=3;
    left=4;
    none=5;
    X=0;
    Y=0;
    direction=none;
}

cCamera::~cCamera() {
}

void cCamera::cameraMovement(bool editMode) {

    //Do Camera movement
    switch(direction) {
    case 1:
        Y += 1;
        break;
    case 2:
        X -= 1;
        break;
    case 3:
        Y -= 1;
        break;
    case 4:
        X += 1;
        break;
    }

    if(!editMode) { // Dont move camera automaticly when in edit mode because we want to move by mouse

        //Let the camera follow the players position. If the camera position is not optimal then increase or decrease the camera position by 1 to have a smooth scrolling effect. Do not follow
        //when the user is jumping..this is kind a hectic.

        //Left/Right
        int iPos = -(oWorld->oPlayerObject->X - (oWorld->oConfig->m_iScreenWidth/2) - oWorld->oPlayerObject->oGFXLayer->fGetWidth());

        if(iPos < X) {
            // Let the Camera go left
            X-=velocity;
        } else if(iPos > X) {
            // Let the Camera go left
            X+=velocity;
        }

        //Up/Down
        if(!oWorld->oPlayerObject->blIsJumping) { //Do not update camera on player jump
            iPos = -(oWorld->oPlayerObject->Y - (oWorld->oConfig->m_iScreenHeight/2) - oWorld->oPlayerObject->oGFXLayer->fGetHeight());
            if(iPos < Y) {
                // Let the Camera go up
                Y-=velocity;
            } else if(iPos > Y) {
                // Let the Camera go down
                Y+=velocity;
            } else {
                // The camera is in optimal position
            }
        }

    }
}
