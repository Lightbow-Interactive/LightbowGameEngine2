#include <iostream>
#include "LBGECore.h"
#include "Source/Levels/PongMenuLevel.h"
#include "LBGEUi.h"

int main()
{
    srand(time(NULL));

    Game::WINDOW_NAME = "LBGE2 - Pong";
    Game::ChangeLevel(new PongMenuLevel());

    Game::Start();

    return 0;
}
