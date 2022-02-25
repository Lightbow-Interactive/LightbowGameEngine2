#include "Player.h"
#include "LBGECore.h"
#include <iostream>
#include "Ball.h"
#include "../Levels/PongPlayingLevel.h"


Player::Player(bool isAiPlayer, int side) : LBGEObject("Resources/paddle.png")
{
    m_isAi = isAiPlayer;

    if (side == 0) SetPosition(100.f, (float)Game::HEIGHT / 2 - GetHeight() / 2);
    if (side == 1) SetPosition((float)Game::WIDTH - 100.f, (float)Game::HEIGHT / 2 - GetHeight() / 2);
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

    if (!m_isAi)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (GetPosition().y-m_speed*deltaTime >= 0.f)
            {
                AddLocalOffset(0, -m_speed * deltaTime);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            //std::cout << "Player " << GetPosition().y << std::endl;
            //std::cout << "Screen " << (float)Game::HEIGHT-GetHeight() << std::endl;
            if (GetPosition().y+m_speed*deltaTime <= (float)Game::HEIGHT - GetHeight())
            {
                AddLocalOffset(0, m_speed * deltaTime);
            }
        }



    }
    else
    {
        PongPlayingLevel* level = dynamic_cast<PongPlayingLevel*>(Game::GetLevel());
        if (!level) return;

        Ball* ball = level->GetBall();
        if (!ball) return;

        // Easy AI:

        float ballY = ball->GetPosition().y;
        float myY = GetPosition().y;

        if (ballY > GetTop())
        {
            if (GetPosition().y+m_speed*deltaTime <= (float)Game::HEIGHT - GetHeight())
                AddLocalOffset(0, m_speed * deltaTime);
        }
        if (ballY < GetBottom()-100.f)
        {
            if (GetPosition().y-m_speed*deltaTime >= 0.f)
                AddLocalOffset(0, -m_speed * deltaTime);
        }

        // Hard AI:

        //SetPosition(GetPosition().x, ball->GetPosition().y);
    }
}
