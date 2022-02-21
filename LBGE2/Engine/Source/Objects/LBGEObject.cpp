#include "LBGEObject.h"
#include <iostream>

LBGEObject::LBGEObject(const std::string &textureFile)
{
    if (!m_texture.loadFromFile(textureFile))
    {
        std::cout << "Unable to load texture ... " << textureFile << std::endl;
        return;
    }
    m_sprite.setTexture(m_texture);
}

LBGEObject::~LBGEObject()
{

}

void LBGEObject::HandleInput(KeyEvent *inputEvent)
{
}

void LBGEObject::Update(float deltaTime)
{
}

void LBGEObject::Render(sf::RenderWindow *window)
{
    window->draw(m_sprite);
}

void LBGEObject::AddLocalOffset(float dx, float dy)
{
    SetPosition(GetPosition().x + dx, GetPosition().y + dy);
}

Vector2<float> LBGEObject::GetPosition()
{
    Vector2<float> pos{};
    pos.x = m_sprite.getPosition().x;
    pos.y = m_sprite.getPosition().y;
    return pos;
}

void LBGEObject::SetPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}
