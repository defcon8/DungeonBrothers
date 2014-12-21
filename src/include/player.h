#ifndef PLAYER_H
#define PLAYER_H
#include <list>
#include "levelobject.h"

using namespace std;

class cWorld;

class cPlayer : public cLevelObject {
private:
    int gravity, velocityy, velocityx, velocityfall, jumprange, jumpstep, lastdirection;
    void moveByUserInput();
    void jumpPhysics();
    void gravityPhysics();
    void setSprite();

public:
    bool moveup, moveright, movedown, moveleft;
    int facedirection;
    bool isjumping;
    void aI();
    void moveDirection(int direction, bool enabled);
    void jump();
    void fire();
    cPlayer(cWorld* _world, char* tilesource, int spriteheight, int spritewidth);
    ~cPlayer();
};

#endif // PLAYER_H


