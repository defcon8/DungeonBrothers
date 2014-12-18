/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/

#ifndef CAMERA_H_
#define CAMERA_H_
class cWorld;

class cCamera {

private:

public:

    cWorld* oWorld;
    int up, right, down, left, none, direction, velocity, X, Y;

    cCamera(cWorld* oWorldRef);
    ~cCamera();

    void cameraMovement();
};

#endif /* CAMERA_H_ */
