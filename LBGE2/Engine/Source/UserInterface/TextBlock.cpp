#include "TextBlock.h"

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
