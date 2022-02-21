#ifndef LBGE2_PLAYER_H
#define LBGE2_PLAYER_H

#include "LBGEObjects.h"

class Player : public LBGEObject
{
public:
    Player(bool isAiPlayer);

    void HandleInput(KeyEvent *inputEvent) override;
    void Update(float deltaTime) override;

private:
    bool isAi;

};


#endif //LBGE2_PLAYER_H
