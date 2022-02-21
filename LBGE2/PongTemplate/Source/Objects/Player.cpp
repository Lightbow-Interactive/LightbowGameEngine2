#include "Player.h"
#include "LBGECore.h"
#include <iostream>
#include "Ball.h"
#include "../Levels/PongPlayingLevel.h"


Player::Player(bool isAiPlayer) : LBGEObject("Resources/paddle.png")
{
    isAi = isAiPlayer;

    if (!isAi) SetPosition(100.f, (float)Game::SCREEN_HEIGHT/2-GetHeight()/2);
    else SetPosition((float)Game::SCREEN_WIDTH-100.f, (float)Game::SCREEN_HEIGHT/2-GetHeight()/2);
}

void Player::HandleInput(KeyEvent *inputEvent)
{
    LBGEObject::HandleInput(inputEvent);

    /*if (inputEvent->type == KeyPressed)
    {
        if (inputEvent->key == sf::Keyboard::Up)
        {
            AddLocalOffset(0, -20.f);
        }
        if (inputEvent->key == sf::Keyboard::Down)
        {
            AddLocalOffset(0, 20.f);
        }
    }*/
}

void Player::Update(float deltaTime)
{
    LBGEObject::Update(deltaTime);

    if (!isAi)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (GetPosition().y-800.f*deltaTime >= 0.f)
                AddLocalOffset(0, -800.f * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (GetPosition().y+800.f*deltaTime <= (float)Game::SCREEN_HEIGHT-GetHeight())
                AddLocalOffset(0, 800.f * deltaTime);
        }
    }
    else
    {
        PongPlayingLevel* level = dynamic_cast<PongPlayingLevel*>(Game::GetLevel());
        if (!level) return;

        Ball* ball = level->GetBall();
        if (!ball) return;

        float ballY = ball->GetPosition().y;
        float myY = GetPosition().y;

        if (ballY > myY)
        {
            if (GetPosition().y+800.f*deltaTime <= (float)Game::SCREEN_HEIGHT-GetHeight())
                AddLocalOffset(0, 800.f * deltaTime);
        }
        if (ballY < myY)
        {
            if (GetPosition().y-800.f*deltaTime >= 0.f)
                AddLocalOffset(0, -800.f * deltaTime);
        }
    }
}
