#include "Sound.h"
#include <iostream>

Sound::Sound(const std::string &file)
{
    if (!m_buffer.loadFromFile(file))
    {
        std::cout << "Cannot load sound .. " << file << std::endl;
    }

    m_sound.setBuffer(m_buffer);
}
