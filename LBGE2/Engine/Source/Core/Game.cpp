#include "Game.h"
#include "../Shader/Shader.h"
#include "Logger.h"
#include <iostream>

int Game::WIDTH;
int Game::HEIGHT;
std::string Game::WINDOW_NAME = "Lightbow Game Engine 2";
int Game::FRAMERATE_LIMIT = 60;
int Game::LAST_FPS = 0;

sf::RenderWindow Game::m_window;
sf::Clock Game::m_clock;
Level* Game::m_level;
sf::Image Game::m_icon;

bool Game::m_editorGameRunning = false;
ImGuiLayer Game::m_imGuiLayer;
sf::RenderTexture Game::m_frameBuffer;

void Game::Start()
{
    if (m_window.isOpen()) return;

    WIDTH = (int)sf::VideoMode::getDesktopMode().width;
    HEIGHT = (int)sf::VideoMode::getDesktopMode().height;

    Shader::CheckAvail();

    m_window.create(sf::VideoMode::getDesktopMode(), WINDOW_NAME);
    m_window.setFramerateLimit(FRAMERATE_LIMIT);
    if (m_icon.loadFromFile("Resources/icon.png"))
        m_window.setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());

    Logger::Log("width " + std::to_string(WIDTH) + " height " + std::to_string(HEIGHT));

    m_level->Init();

    GameLoop();

    delete m_level;
    m_window.close();
}

void Game::StartEditor()
{
    if (m_window.isOpen()) return;

    Shader::CheckAvail();

    WIDTH = sf::VideoMode::getDesktopMode().width/1.7;
    HEIGHT = sf::VideoMode::getDesktopMode().height/1.7f;

    m_window.create(sf::VideoMode::getDesktopMode(), WINDOW_NAME + " - Editor");
    m_frameBuffer.create(WIDTH, HEIGHT);

    m_window.setFramerateLimit(FRAMERATE_LIMIT);
    if (m_icon.loadFromFile("Resources/editor.png"))
        m_window.setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());

    m_imGuiLayer.Init(m_window);

    m_level->Init();

    GameLoopEditor();

    m_imGuiLayer.ShutDown();
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

        m_window.clear(sf::Color::White);

        sf::Event event{};
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) m_window.close();
            if (event.type == sf::Event::Resized)
            {
                WIDTH = (int)event.size.width;
                HEIGHT = (int)event.size.height;
            }
            m_level->HandleInput(&event);
        }

        m_level->UpdateLevel(elapsedSeconds);

        m_level->RenderLevel(&m_window);

        m_window.display();
    }
}

void Game::GameLoopEditor()
{
    while (m_window.isOpen())
    {
        if (!m_level) return;

        sf::Time timeElapsed = m_clock.restart();
        int elapsedMillis = timeElapsed.asMilliseconds();
        float elapsedSeconds = timeElapsed.asSeconds();

        LAST_FPS = 1000 / elapsedMillis;

        m_window.clear(sf::Color::Black);
        m_frameBuffer.clear(sf::Color::White);


        sf::Event event{};
        while (m_window.pollEvent(event))
        {
            m_imGuiLayer.OnEvent(m_window, event);

            if (event.type == sf::Event::Closed) m_window.close();
            if (event.type == sf::Event::Resized)
            {
                WIDTH = (int)event.size.width;
                HEIGHT = (int)event.size.height;
            }

            if (m_editorGameRunning) m_level->HandleInput(&event);
        }

        if (m_editorGameRunning) m_level->UpdateLevel(elapsedSeconds);
        m_imGuiLayer.Update(m_window, timeElapsed);

        m_level->RenderLevel(&m_frameBuffer);
        m_imGuiLayer.ProcessGui();
        m_imGuiLayer.Render(m_window);

        m_window.display();
    }
}

void Game::ChangeLevel(Level *level)
{
    m_level = level;
    if (m_level) m_level->Init();
}

Level *Game::GetLevel()
{
    return m_level;
}

void Game::SetStartupLevel(Level* level)
{
    m_level = level;
}

void Game::ResetGameEditor()
{
    m_frameBuffer.create(WIDTH, HEIGHT);
    m_frameBuffer.clear(sf::Color::White);

    m_level->Init();
    SetGameRunningEditor(false);
}
