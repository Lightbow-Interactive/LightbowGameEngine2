
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
    void UpdateLevel(float deltaTime) override;

    Ball* GetBall() { return m_ball; }
    void BallDidHitWall();
    void IncreaseScore();

private:
    Player* m_player;
    Player* m_aiPlayer;
    Ball* m_ball;
    int m_playerLives;
    TextBlock* m_livesText;
    int m_score;
    TextBlock* m_scoreText;


};


#endif //LBGE2_PONGPLAYINGLEVEL_H
