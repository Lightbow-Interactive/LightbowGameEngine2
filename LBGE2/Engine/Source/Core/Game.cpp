#include "Game.h"

int Game::SCREEN_WIDTH = 1920;
int Game::SCREEN_HEIGHT = 1080;
std::string Game::WINDOW_NAME = "Lightbow Game Engine 2";
int Game::FRAMERATE_LIMIT = 60;

sf::RenderWindow Game::m_window;
sf::Clock Game::m_clock;
Level* Game::m_level;
sf::Image Game::m_icon;

void Game::Start()
{
    if (m_window.isOpen()) return;



    m_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32),
                    WINDOW_NAME);
    m_window.setFramerateLimit(FRAMERATE_LIMIT);
    if (m_icon.loadFromFile("Resources/icon.png"))
        m_window.setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());

    m_level->Init();

    GameLoop();

    delete m_level;
    m_window.close();
}

void Game::GameLoop()
{
    while (m_window.isOpen())
    {
        if (!m_level) return;

        float elapsedMillis = m_clock.restart().asMilliseconds();
        float elapsedSeconds = elapsedMillis/1000.f;

        m_window.clear(sf::Color::White);

        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) m_window.close();
            m_level->HandleInput(&event);
        }

        m_level->UpdateLevel(elapsedSeconds);

        m_level->RenderLevel(&m_window);

        m_window.display();
    }
}

void Game::SetLevel(Level *level)
{
    m_level = level;
    if (m_level) m_level->Init();
}

Level *Game::GetLevel()
{
    return m_level;
}
