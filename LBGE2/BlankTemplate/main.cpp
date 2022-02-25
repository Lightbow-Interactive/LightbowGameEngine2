#include "LBGECore.h"
#include "Source/MainLevel.h"

int main()
{
    Game::WINDOW_NAME = "LBGE2 - Blank Template";
    Game::SetStartupLevel(new MainLevel());

    Game::StartEditor();

    return 0;
}
