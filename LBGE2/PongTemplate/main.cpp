#include <iostream>
#include "LBGECore.h"
#include "Source/Levels/PongMenuLevel.h"
#include "LBGEUi.h"

int main()
{
    srand(time(NULL));

    Game::FRAMERATE_LIMIT = 120;
    Game::WINDOW_NAME = "LBGE2 - Pong";
    Game::SetStartupLevel(new PongMenuLevel());

    Game::StartEditor();

    return 0;
}
