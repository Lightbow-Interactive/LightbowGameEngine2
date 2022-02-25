
#ifndef LBGE2_OBJECTMANAGER_H
#define LBGE2_OBJECTMANAGER_H

#include "LBGEObject.h"
#include "SFML/Graphics.hpp"

class ObjectManager
{
public:
    ~ObjectManager();
    void Add(const std::string& name, LBGEObject* object);
    void Remove(const std::string& name);

    void HandleInputAll(sf::Event* event);
    void UpdateAll(float deltaTime);
    void RenderAll(sf::RenderWindow* window);
    void RenderAll(sf::RenderTexture* rtexture);

    std::map<std::string, LBGEObject*>* GetAllObjects() { return &m_objects; }

private:
    std::map<std::string, LBGEObject*> m_objects;

};


#endif //LBGE2_OBJECTMANAGER_H
