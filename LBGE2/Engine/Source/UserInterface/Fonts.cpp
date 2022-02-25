#include "Fonts.h"

std::map<std::string, sf::Font*> Fonts::m_fonts;

void Fonts::Add(const std::string &name, const std::string &file)
{
    sf::Font* newFont = new sf::Font();
    if (newFont->loadFromFile(file))
        m_fonts.insert(std::pair<std::string, sf::Font*>(name, newFont));
}

void Fonts::Remove(const std::string &name)
{

}

sf::Font *Fonts::Get(const std::string &name)
{
    auto results = m_fonts.find(name);
    if (results != m_fonts.end())
    {
        return results->second;
    }
    return nullptr;
}

std::string Fonts::GetFontName(sf::Font* font)
{
    auto itr = m_fonts.begin();
    while (itr != m_fonts.end())
    {
        if (itr->second == font)
        {
            return itr->first;
        }
        itr++;
    }
    return "";
}
