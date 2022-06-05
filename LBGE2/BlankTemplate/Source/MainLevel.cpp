#include "MainLevel.h"
#include <iostream>

void MainLevel::Init()
{
    // Allways set a game state
    m_state = new GameState();
    // Then call to super class
    Level::Init();

    // Further initialization:

    m_map = new Map("Resources/demo.tmx");
    m_map->LoadMap();
    m_map->AddLayer(0);
    m_map->AddLayer(1);
    m_map->AddLayer(2);
    m_map->SetRenderUpToLayer(2);

    Fonts::Add("Poppins", "Resources/Poppins-Regular.ttf");

    m_textBlock = new TextBlock(Fonts::Get("Poppins"), 80);
    m_textBlock->SetText("Blank Template");

    std::cout << (float)Game::WIDTH << " / 2 - " << m_textBlock->GetTextWidth() << " / 2 " << std::endl;
    std::cout << (float)Game::HEIGHT << " / 2 - " << m_textBlock->GetTextHeight() << " / 2 " << std::endl;

    m_textBlock->SetTextPosition((float)Game::WIDTH / 2.f - m_textBlock->GetTextWidth() / 2.f,
                                 (float)Game::HEIGHT / 2.f - m_textBlock->GetTextHeight() / 2.f);

    m_manager.Add("TextBlock1", m_textBlock);
}
