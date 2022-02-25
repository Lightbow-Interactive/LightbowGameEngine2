#include "LBGECore.h"
#include "Source/MainLevel.h"

int main()
{
    Game::WINDOW_NAME = "LBGE2 - Blank Template";
    Game::SetLevel(new MainLevel());

    // Start Normal Game:
    Game::Start();
    
    // Start Editor:
    //Game::StartEditor();

    return 0;
}
