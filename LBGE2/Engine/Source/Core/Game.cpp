#include "Game.h"
#include "../Shader/Shader.h"
#include <iostream>

int Game::SCREEN_WIDTH = 1920;
int Game::SCREEN_HEIGHT = 1080;
std::string Game::WINDOW_NAME = "Lightbow Game Engine 2";
int Game::FRAMERATE_LIMIT = 60;

sf::RenderWindow Game::m_window;
sf::Clock Game::m_clock;
Level* Game::m_level;
sf::Image Game::m_icon;

bool Game::m_editor = true;
ImGuiLayer Game::m_imGuiLayer;
sf::RenderTexture Game::m_frameBuffer;

void Game::Start()
{
    if (m_window.isOpen()) return;

    Shader::CheckAvail();

    if (m_editor)
    {
        m_window.create(sf::VideoMode(SCREEN_WIDTH*2, SCREEN_HEIGHT*2, 32),
                        WINDOW_NAME + " - Editor");
        m_frameBuffer.create(SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    else
    {
        m_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32),
                        WINDOW_NAME);
    }

    m_window.setFramerateLimit(FRAMERATE_LIMIT);
    if (m_icon.loadFromFile("Resources/icon.png"))
        m_window.setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());

    if (m_editor) m_imGuiLayer.Init(m_window);


    m_level->Init();

    GameLoop();

    if (m_editor) m_imGuiLayer.ShutDown();
    delete m_level;
    m_window.close();
}

void Game::GameLoop()
{
    while (m_window.isOpen())
    {
        if (!m_level) return;

        sf::Time timeElapsed = m_clock.restart();
        int elapsedMillis = timeElapsed.asMilliseconds();
        float elapsedSeconds = timeElapsed.asSeconds();

        if (m_editor)
        {
            m_window.clear(sf::Color::Black);
            m_frameBuffer.clear(sf::Color::White);
        }
        else
        {
            m_window.clear(sf::Color::White);
        }


        sf::Event event{};
        while (m_window.pollEvent(event))
        {
            if (m_editor) m_imGuiLayer.OnEvent(m_window, event);

            if (event.type == sf::Event::MouseButtonPressed)
            {
                std::cout << "x = " << event.mouseButton.x << "  y = " << event.mouseButton.y << std::endl;
            }

            if (event.type == sf::Event::Closed) m_window.close();
            if (event.type == sf::Event::Resized)
            {
                SCREEN_WIDTH = (int)event.size.width;
                SCREEN_HEIGHT = (int)event.size.height;
            }
            m_level->HandleInput(&event);
        }

        m_level->UpdateLevel(elapsedSeconds);
        if (m_editor) m_imGuiLayer.Update(m_window, timeElapsed);

        if (m_editor) m_level->RenderLevel(&m_frameBuffer);
        else m_level->RenderLevel(&m_window);

        if (m_editor)
        {
            m_imGuiLayer.ProcessGui();
        }

        if (m_editor) m_imGuiLayer.Render(m_window);

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
