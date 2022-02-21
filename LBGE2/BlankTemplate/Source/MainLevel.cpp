
#include "MainLevel.h"

void MainLevel::Init()
{
    // Allways set a game state
    m_state = new GameState();
    // Then call to super class
    Level::Init();

    // Further initialization:

    Fonts::Add("Poppins", "Resources/Poppins-Regular.ttf");

    m_textBlock = new TextBlock(Fonts::Get("Poppins"), 80);
    m_textBlock->SetText("Blank Template");
    m_textBlock->SetTextPosition((float)Game::SCREEN_WIDTH/2-m_textBlock->GetTextWidth()/2,
                                 (float)Game::SCREEN_HEIGHT/2-m_textBlock->GetTextHeight()/2);
    m_manager.Add("TextBlock1", m_textBlock);
}
