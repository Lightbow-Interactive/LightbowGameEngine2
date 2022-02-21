
#ifndef LBGE2_PONGPLAYINGLEVEL_H
#define LBGE2_PONGPLAYINGLEVEL_H

#include "LBGECore.h"
#include "../Objects/Player.h"
#include "../Objects/Ball.h"
#include "LBGEUi.h"

class PongPlayingLevel : public Level
{
public:
    ~PongPlayingLevel() override;
    void Init() override;

    Ball* GetBall() { return m_ball; }
    void BallDidHitWall();

private:
    Player* m_player;
    Player* m_aiPlayer;
    Ball* m_ball;
    int m_playerLives;
    TextBlock* m_livesText;


};


#endif //LBGE2_PONGPLAYINGLEVEL_H
