#ifndef LBGE2_FONTS_H
#define LBGE2_FONTS_H

#include "SFML/Graphics.hpp"

class Fonts
{
public:
    static void Add(const std::string& name, const std::string& file);
    static void Remove(const std::string& name);
    static sf::Font* Get(const std::string& name);

private:
    static std::map<std::string, sf::Font*> m_fonts;

};


#endif //LBGE2_FONTS_H
