#ifndef LBGE2_LBGEOBJECT_H
#define LBGE2_LBGEOBJECT_H

#include "SFML/Graphics.hpp"
#include "../Types/KeyEvent.h"
#include "../Types/Vector.h"
#include "../Core/EventDelegate.h"
#include "../Shader/Shader.h"
#include "Components/ObjectComponent.h"

class LBGEObject
{
public:
    LBGEObject(const std::string& textureFile);
    virtual ~LBGEObject();

    virtual void HandleInput(KeyEvent* inputEvent);
    virtual void Update(float deltaTime);
    virtual void Render(sf::RenderWindow* window);
    virtual void Render(sf::RenderTexture* rtexture);

    void AddLocalOffset(float dx, float dy);
    void AddLocalOffset(const Vector2<float>& offset) { AddLocalOffset(offset.x, offset.y); }
    void SetPosition(float x, float y);
    void SetPosition(const Vector2<float>& position) { SetPosition(position.x, position.y); }
    void SetScale(float sx, float sy) { m_sprite.setScale(sx, sy); }
    void SetScale(const Vector2<float>& scaleVector) { SetScale(scaleVector.x, scaleVector.y); }
    Vector2<float> GetPosition();
    float GetWidth() const { return m_sprite.getGlobalBounds().width; }
    float GetHeight() const { return m_sprite.getGlobalBounds().height; }
    sf::Sprite* GetSprite() { return &m_sprite; }
    float GetTop();
    float GetRight();
    float GetBottom();
    float GetLeft();
    float GetRotation() { return m_sprite.getRotation(); }
    void SetRotation(float newRot) { m_sprite.setRotation(newRot); }
    Vector2<float> GetScale();
    void SetEditorDrawOutline(bool drawOutline) { m_editorDrawOutline = drawOutline; }

    ObjectComponent* GetComponentByName(const std::string& name);
    std::map<std::string, ObjectComponent*>* GetComponents() { return &m_components; }
    void RemoveComponent(const std::string& name);


    template<class T>
    void CreateComponent(const std::string& name)
    {
        ObjectComponent* component = new T(this);
        if (!component) return;
        m_components.insert(std::pair<std::string, ObjectComponent*>(name, component));
    }

    template<typename T>
    T* GetComponentByName(const std::string& name)
    {
        auto found = m_components.find(name);
        if (found != m_components.end())
        {
            T* component = dynamic_cast<T*>(found->second);
            if (component) return component;
        }
        return nullptr;
    }

    const std::string* GetTextureFile() { return &m_textureFile; }
    void SetTexture(const std::string& textureFile);
    Shader* GetShader() { return &m_shader; }

    virtual void OnCollidesWith(LBGEObject* other) {}
    EventDelegate OnMouseClickOnObject;

protected:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    Shader m_shader;
    bool m_editorDrawOutline = false;

    void InitComponents();

private:
    std::map<std::string, ObjectComponent*> m_components;
    std::string m_textureFile;

    void UpdateComponents(float deltaTime);

};


#endif //LBGE2_LBGEOBJECT_H
