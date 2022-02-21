#ifndef LBGE2_TEXTBLOCK_H
#define LBGE2_TEXTBLOCK_H

#include "../Objects/LBGEObject.h"

class TextBlock : public LBGEObject
{
public:
    TextBlock(sf::Font* font, int size);

    void Render(sf::RenderWindow *window) override;

    void SetText(const std::string& text) { m_text.setString(text); }
    float GetTextWidth() { return m_text.getGlobalBounds().width; }
    float GetTextHeight() { return m_text.getGlobalBounds().height; }
    void SetTextPosition(float x, float y) { m_text.setPosition(x, y); }

private:
    sf::Text m_text;

};


#endif //LBGE2_TEXTBLOCK_H
