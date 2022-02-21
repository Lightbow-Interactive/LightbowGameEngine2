#include "PongMenuLevel.h"
#include "../States/PongMenuState.h"
#include "LBGEObjects.h"
#include "PongPlayingLevel.h"
#include <iostream>

void PongMenuLevel::Init()
{
    m_state = new PongMenuState();
    Level::Init();

    LBGEObject* playButton = new LBGEObject("Resources/button_play.png");
    playButton->SetScale(2.f, 2.f);
    playButton->SetPosition((float)Game::SCREEN_WIDTH/2-playButton->GetWidth()/2,
                            (float)Game::SCREEN_HEIGHT/2-playButton->GetHeight()/2);
    playButton->OnMouseClickOnObject.Bind([]()->void
    {
        std::cout << "Clicked on play button" << std::endl;
        Game::SetLevel(new PongPlayingLevel());
    });
    m_manager.Add("PlayButton", playButton);
}