#ifndef LBGE2_TEXTBLOCK_H
#define LBGE2_TEXTBLOCK_H

#include "../Objects/LBGEObject.h"

class TextBlock : public LBGEObject
{
public:
    TextBlock(sf::Font* font, int size);

    void Render(sf::RenderWindow *window) override;
    void Render(sf::RenderTexture* rtexture) override;

    void SetText(const std::string& text) { m_text.setString(text); }
    float GetTextWidth() { return m_text.getGlobalBounds().width; }
    float GetTextHeight() { return m_text.getGlobalBounds().height; }
    void SetTextPosition(float x, float y) { m_text.setPosition(x, y); }
    std::string GetText() { return m_text.getString().toAnsiString(); }
    unsigned int GetFontSize() { return m_text.getCharacterSize(); }
    void SetFontSize(int val) { m_text.setCharacterSize(val); }
    const sf::Font* GetFont() { return m_text.getFont(); }
    void SetFont(const std::string& name);
    const std::string* GetFontFile() { return &m_fontFile; }
    void SetFontByFile(const std::string& fontFile);


private:
    std::string m_fontFile;
    sf::Font m_font;
    sf::Text m_text;

};


#endif //LBGE2_TEXTBLOCK_H
