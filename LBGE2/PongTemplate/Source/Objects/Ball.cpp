#include "Ball.h"
#include "LBGECore.h"
#include "Player.h"
#include <cmath>

Ball::Ball() : LBGEObject("Resources/ball.png")
{
    SetPosition((float)Game::SCREEN_WIDTH/2, (float)Game::SCREEN_HEIGHT/2);
    m_speed = 500.f;
    m_angle = rand() % 180;
}

void Ball::Update(float deltaTime)
{
    LBGEObject::Update(deltaTime);

    float velocity = m_speed * deltaTime;
    float angleRad = m_angle * M_PI / 180.f;

    float velocityX = velocity * std::cos(angleRad) - 0 * std::sin(angleRad);
    float velocityY = 0 * std::cos(angleRad) + velocity * std::sin(angleRad);

    // Bounce on top and bottom walls
    if (GetTop() + velocityY <= 0 || GetBottom() + velocityY >= (float)Game::SCREEN_HEIGHT)
    {
        m_angle = 360 - m_angle;
        velocityY *= -1;
    }

    // Bounce on right and left wall
    if (GetLeft() + velocityX <= 0 || GetRight() + velocityX >= (float)Game::SCREEN_WIDTH)
    {
        m_angle = (180 - m_angle) % 360;
        velocityX *= -1;
    }

    AddLocalOffset(velocityX, velocityY);
}

void Ball::OnCollidesWith(LBGEObject *other)
{
    LBGEObject::OnCollidesWith(other);

    if (!dynamic_cast<Player*>(other)) return;

    float paddleCenterY = (other->GetTop() + other->GetBottom()) / 2;
    float ballCenterY = (GetTop() + GetBottom()) / 2;

    float distDiff = ballCenterY - paddleCenterY;
    float maxDiff = other->GetHeight();

    float normalizedDiff = distDiff / maxDiff;

    m_angle = (int)(normalizedDiff * 90);

    m_speed += 100.f;
    if (m_speed > 1800.f) m_speed = 1800.f;
}
