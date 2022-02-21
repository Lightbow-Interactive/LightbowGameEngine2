#include "Audio.h"

void Audio::PlaySound2D(Sound *sound)
{
    sf::Sound* sfmlSound = sound->GetSFMLSound();
    if (sfmlSound) sfmlSound->play();
}
