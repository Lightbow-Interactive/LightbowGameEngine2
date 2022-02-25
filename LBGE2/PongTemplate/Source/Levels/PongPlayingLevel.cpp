#include "PongPlayingLevel.h"
#include "PongMenuLevel.h"

PongPlayingLevel::~PongPlayingLevel()
{
    delete m_state;
    delete m_player;
    delete m_aiPlayer;
    delete m_ball;
    delete m_livesText;
    delete m_scoreText;
}

void PongPlayingLevel::Init()
{
    m_state = new GameState();
    Level::Init();

    m_playerLives = 3;
    m_score = 0;

    Fonts::Add("Poppins", "Resources/Poppins-Medium.ttf");

    m_livesText = new TextBlock(Fonts::Get("Poppins"), 50);
    m_livesText->SetText("Lives: " + std::to_string(m_playerLives));
    m_livesText->SetTextPosition(10.f, (float)Game::HEIGHT - m_livesText->GetTextHeight() * 2);
    m_manager.Add("LivesText", m_livesText);

    m_scoreText = new TextBlock(Fonts::Get("Poppins"), 50);
    m_scoreText->SetText("Score: " + std::to_string(m_score));
    m_scoreText->SetTextPosition(10.f, 10.f);
    m_manager.Add("ScoreText", m_scoreText);

    m_player = new Player(false, 0);
    m_manager.Add("Player", m_player);

    m_ball = new Ball();
    //m_manager.Add("Ball", m_ball);

    m_aiPlayer = new Player(true, 1);
    m_manager.Add("AiPlayer", m_aiPlayer);
}

void PongPlayingLevel::UpdateLevel(float deltaTime)
{
    if (m_playerLives >= 0) Level::UpdateLevel(deltaTime);
}

void PongPlayingLevel::BallDidHitWall()
{
    if (--m_playerLives < 0)
    {
        // End Game
        //Game::ChangeLevel(new PongMenuLevel());
    }
    else
    {
        m_livesText->SetText("Lives: " + std::to_string(m_playerLives));
        m_livesText->SetTextPosition(10.f, (float)Game::HEIGHT - m_livesText->GetTextHeight() * 2);
    }
}

void PongPlayingLevel::IncreaseScore()
{
    ++m_score;
    m_scoreText->SetText("Score: " + std::to_string(m_score));
    m_scoreText->SetTextPosition(10.f, 10.f);
}


