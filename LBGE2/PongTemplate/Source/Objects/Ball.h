#ifndef LBGE2_BALL_H
#define LBGE2_BALL_H

#include "LBGEObjects.h"

class Ball : public LBGEObject
{
public:
    Ball();
    void Update(float deltaTime) override;
    void OnCollidesWith(LBGEObject *other) override;

private:
    int m_angle;
    float m_speed;

};


#endif //LBGE2_BALL_H
