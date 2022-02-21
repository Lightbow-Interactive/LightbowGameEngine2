#ifndef LBGE2_GAMESTATE_H
#define LBGE2_GAMESTATE_H

#include "SFML/Graphics.hpp"

class GameState
{
public:
    virtual ~GameState();
    virtual void Init();
    virtual void HandleInput(sf::Event* event);
    virtual void Update(float deltaTime);
    virtual void Render(sf::RenderWindow* window);

};


#endif //LBGE2_GAMESTATE_H
