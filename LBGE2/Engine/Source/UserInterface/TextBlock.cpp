#include "TextBlock.h"
#include "Fonts.h"

TextBlock::TextBlock(sf::Font *font, int size) : LBGEObject("")
{
    m_text.setFont(*font);
    m_text.setCharacterSize(size);
    m_text.setFillColor(sf::Color::Black);
}

void TextBlock::Render(sf::RenderWindow *window)
{
    window->draw(m_text);
}

void TextBlock::Render(sf::RenderTexture *rtexture)
{
    rtexture->draw(m_text);
}

void TextBlock::SetFont(const std::string &name)
{
    sf::Font* font = Fonts::Get(name);
    if (font)
    {
        m_text.setFont(*font);
    }
}
