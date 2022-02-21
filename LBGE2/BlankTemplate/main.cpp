#include "LBGECore.h"
#include "Source/MainLevel.h"

int main()
{
    Game::WINDOW_NAME = "LBGE2 - Blank Template";
    Game::SetLevel(new MainLevel());

    Game::Start();

    return 0;
}
