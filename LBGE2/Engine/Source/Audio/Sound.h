
#ifndef LBGE2_SOUND_H
#define LBGE2_SOUND_H

#include "SFML/Audio.hpp"

class Sound
{
public:
    Sound(const std::string& file);

    sf::Sound* GetSFMLSound() { return &m_sound; }

private:
    sf::SoundBuffer m_buffer;
    sf::Sound m_sound;

};


#endif //LBGE2_SOUND_H
