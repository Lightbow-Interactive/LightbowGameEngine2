#include "PongPlayingLevel.h"

PongPlayingLevel::~PongPlayingLevel()
{
    delete m_state;
    delete m_player;
    delete m_aiPlayer;
    delete m_ball;
}

void PongPlayingLevel::Init()
{
    m_state = new GameState();
    Level::Init();

    m_player = new Player(false);
    m_manager.Add("Player", m_player);

    m_ball = new Ball();
    m_manager.Add("Ball", m_ball);

    m_aiPlayer = new Player(true);
    m_manager.Add("AiPlayer", m_aiPlayer);
}


