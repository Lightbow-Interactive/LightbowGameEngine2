#ifndef LBGE2_KEYEVENT_H
#define LBGE2_KEYEVENT_H

#include "SFML/Graphics.hpp"
#include "Vector.h"

enum EKeyEventType
{
    KeyPressed,
    KeyReleased,
    MouseClick
};

struct KeyEvent
{
    EKeyEventType type;
    Vector2<float> location;
    sf::Keyboard::Key key;
};

#endif //LBGE2_KEYEVENT_H
