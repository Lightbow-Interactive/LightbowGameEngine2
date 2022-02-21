
#ifndef LBGE2_PONGPLAYINGLEVEL_H
#define LBGE2_PONGPLAYINGLEVEL_H

#include "LBGECore.h"
#include "../Objects/Player.h"
#include "../Objects/Ball.h"

class PongPlayingLevel : public Level
{
public:
    ~PongPlayingLevel() override;
    void Init() override;

    Ball* GetBall() { return m_ball; }

private:
    Player* m_player;
    Player* m_aiPlayer;
    Ball* m_ball;

};


#endif //LBGE2_PONGPLAYINGLEVEL_H
