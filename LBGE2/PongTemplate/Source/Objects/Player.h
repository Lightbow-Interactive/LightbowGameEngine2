#ifndef LBGE2_PLAYER_H
#define LBGE2_PLAYER_H

#include "LBGEObjects.h"

class Player : public LBGEObject
{
public:
    Player(bool isAiPlayer, int side);

    void HandleInput(KeyEvent *inputEvent) override;
    void Update(float deltaTime) override;

    void UpdateSpeed() { m_speed += 100.f; }

private:
    bool m_isAi;
    float m_speed = 800.f;

};


#endif //LBGE2_PLAYER_H
