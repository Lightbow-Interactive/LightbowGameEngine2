#ifndef LBGE2_LBGEOBJECT_H
#define LBGE2_LBGEOBJECT_H

#include "SFML/Graphics.hpp"
#include "../Types/KeyEvent.h"
#include "../Types/Vector.h"

class LBGEObject
{
public:
    LBGEObject(const std::string& textureFile);
    virtual ~LBGEObject();

    virtual void HandleInput(KeyEvent* inputEvent);
    virtual void Update(float deltaTime);
    virtual void Render(sf::RenderWindow* window);

    void AddLocalOffset(float dx, float dy);
    void AddLocalOffset(const Vector2<float>& offset) { AddLocalOffset(offset.x, offset.y); }
    void SetPosition(float x, float y);
    void SetPosition(const Vector2<float>& position) { SetPosition(position.x, position.y); }
    void SetScale(float sx, float sy) { m_sprite.setScale(sx, sy); }
    void SetScale(const Vector2<float>& scaleVector) { SetScale(scaleVector.x, scaleVector.y); }
    Vector2<float> GetPosition();
    float GetWidth() const { return m_sprite.getGlobalBounds().width; }
    float GetHeight() const { return m_sprite.getGlobalBounds().height; }

    virtual void OnCollidesWith(LBGEObject* other) {}
    virtual void OnClickOnObject() {}

protected:
    sf::Texture m_texture;
    sf::Sprite m_sprite;



};


#endif //LBGE2_LBGEOBJECT_H
