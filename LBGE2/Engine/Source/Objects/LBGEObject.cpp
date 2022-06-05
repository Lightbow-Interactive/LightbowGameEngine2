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
    m_textureFile = textureFile;
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

    if (m_editorDrawOutline)
    {
        // todo: draw an outline
    }
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

Vector2<float> LBGEObject::GetScale()
{
    sf::Vector2<float> scale = m_sprite.getScale();
    return {scale.x, scale.y};
}

ObjectComponent *LBGEObject::GetComponentByName(const std::string &name)
{
    auto found = m_components.find(name);
    if (found != m_components.end())
    {
        return found->second;
    }
    return nullptr;
}

void LBGEObject::InitComponents()
{
    auto itr = m_components.begin();
    while (itr != m_components.end())
    {
        itr->second->Init();
        itr++;
    }
}

void LBGEObject::UpdateComponents(float deltaTime)
{
    auto itr = m_components.begin();
    while (itr != m_components.end())
    {
        itr->second->UpdateComponent(deltaTime);
        itr++;
    }
}

void LBGEObject::RemoveComponent(const std::string &name)
{
    auto found = m_components.find(name);
    if (found != m_components.end())
    {
        delete found->second;
        m_components.erase(found);
    }
}


void LBGEObject::SetTexture(const std::string &textureFile)
{
    if (!m_texture.loadFromFile(textureFile))
    {
        return;
    }
    
    m_textureFile = textureFile;
    m_sprite.setTexture(m_texture);
}
