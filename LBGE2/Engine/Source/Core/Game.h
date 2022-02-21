#ifndef LBGE2_GAME_H
#define LBGE2_GAME_H

#include "SFML/Graphics.hpp"
#include "Level.h"

class Game
{
public:
    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;

    static void Start();
    static void GameLoop();

    static void SetLevel(Level* level);
    static Level* GetLevel();

private:
    static sf::RenderWindow m_window;
    static sf::Clock m_clock;
    static Level* m_level;

};


#endif //LBGE2_GAME_H
