#include <iostream>
#include "LBGECore.h"
#include "Source/Levels/PongMenuLevel.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Game::SetLevel(new PongMenuLevel());
    Game::Start();
    return 0;
}
