#ifndef LBGE2_BALL_H
#define LBGE2_BALL_H

#include "LBGEObjects.h"
#include "LBGEAudio.h"
#include "Player.h"

class Ball : public LBGEObject
{
public:
    Ball();
    ~Ball();
    void Update(float deltaTime) override;
    void OnCollidesWith(LBGEObject *other) override;

private:
    int m_angle;
    float m_speed;
    Sound* m_bounceSound;
    Sound* m_bounceSound2;
    Sound* m_ballLostSound;

};


#endif //LBGE2_BALL_H
