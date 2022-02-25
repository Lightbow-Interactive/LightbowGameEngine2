#include "LBGEObject.h"
#include "../Core/Logger.h"
#include <iostream>

LBGEObject::LBGEObject(const std::string &textureFile)
{
    if (!m_texture.loadFromFile(textureFile))
    {
        Logger::Log("Unable to load texture ... " + textureFile);
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
    if (Shader::ISAVAIL) window->draw(m_sprite, m_shader.GetShaderRef());
    else window->draw(m_sprite);
}

void LBGEObject::Render(sf::RenderTexture *rtexture)
{
    if (Shader::ISAVAIL) rtexture->draw(m_sprite, m_shader.GetShaderRef());
    else rtexture->draw(m_sprite);
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

float LBGEObject::GetTop()
{
    return m_sprite.getGlobalBounds().top;
}

float LBGEObject::GetRight()
{
    return m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width;
}

float LBGEObject::GetBottom()
{
    return m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height;
}

float LBGEObject::GetLeft()
{
    return m_sprite.getGlobalBounds().left;
}


