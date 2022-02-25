#include "Level.h"

Level::~Level()
{
    delete m_state;
}

void Level::Init()
{
    m_state->Init();
}

void Level::UpdateLevel(float deltaTime)
{
    m_state->Update(deltaTime);
    m_manager.UpdateAll(deltaTime);
}

void Level::RenderLevel(sf::RenderWindow *window)
{
    m_state->Render(window);
    m_manager.RenderAll(window);
}

void Level::RenderLevel(sf::RenderTexture *rtexture)
{
    m_manager.RenderAll(rtexture);
}

void Level::HandleInput(sf::Event *event)
{
    m_state->HandleInput(event);
    m_manager.HandleInputAll(event);
}

void Level::SetState(GameState *state)
{
    m_state = state;
}

GameState *Level::GetState()
{
    return m_state;
}