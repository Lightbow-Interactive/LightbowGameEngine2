#include <iostream>
#include "LBGECore.h"
#include "Source/Levels/PongMenuLevel.h"
#include "LBGEUi.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    srand(time(NULL));


    Game::SetLevel(new PongMenuLevel());
    Game::Start();
    return 0;
}
