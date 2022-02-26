#include "LBGECore.h"
#include "MainLevel.h"

int main()
{
    Game::FRAMERATE_LIMIT = 120;
    Game::WINDOW_NAME = "LBGE2 - Blank Template";
    Game::SetStartupLevel(new MainLevel());


    // Start Normal Game:
    //Game::Start();
    
    // Start Editor:
    Game::StartEditor();

    return 0;
}
