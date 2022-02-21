#include "PongPlayingLevel.h"
#include "PongMenuLevel.h"

PongPlayingLevel::~PongPlayingLevel()
{
    delete m_state;
    delete m_player;
    delete m_aiPlayer;
    delete m_ball;
    delete m_livesText;
}

void PongPlayingLevel::Init()
{
    m_state = new GameState();
    Level::Init();

    m_playerLives = 3;

    Fonts::Add("Poppins", "Resources/Poppins-Medium.ttf");

    m_livesText = new TextBlock(Fonts::Get("Poppins"), 50);
    m_livesText->SetText("Lives: " + std::to_string(m_playerLives));
    m_livesText->SetTextPosition(10.f,(float)Game::SCREEN_HEIGHT - m_livesText->GetTextHeight()*2);
    m_manager.Add("LivesText", m_livesText);

    m_player = new Player(false, 0);
    m_manager.Add("Player", m_player);

    m_ball = new Ball();
    m_manager.Add("Ball", m_ball);

    m_aiPlayer = new Player(true, 1);
    m_manager.Add("AiPlayer", m_aiPlayer);
}

void PongPlayingLevel::BallDidHitWall()
{
    if (--m_playerLives < 0)
    {
        // End Game
        Game::SetLevel(new PongMenuLevel());
    }
    else
    {
        m_livesText->SetText("Lives: " + std::to_string(m_playerLives));
        m_livesText->SetTextPosition(10.f,(float)Game::SCREEN_HEIGHT - m_livesText->GetTextHeight()*2);
    }
}


