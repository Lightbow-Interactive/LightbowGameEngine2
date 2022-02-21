
#include "ObjectManager.h"
#include "../Types/KeyEvent.h"

ObjectManager::~ObjectManager()
{
    auto itr = m_objects.begin();
    while (itr != m_objects.end())
    {
        delete itr->second;
        itr++;
    }
}

void ObjectManager::Add(const std::string &name, LBGEObject *object)
{
    m_objects.insert(std::pair<std::string, LBGEObject*>(name, object));
}

void ObjectManager::Remove(const std::string &name)
{
    auto results = m_objects.find(name);
    if (results != m_objects.end())
    {
        delete results->second;
        m_objects.erase(results);
    }
}

void ObjectManager::HandleInputAll(sf::Event *event)
{
    bool isEvent = false;
    KeyEvent inputEvent{};

    if (event->type == sf::Event::KeyPressed)
    {
        inputEvent.type = KeyPressed;
        inputEvent.key = event->key.code;
        isEvent = true;
    }

    if (event->type == sf::Event::KeyReleased)
    {
        inputEvent.type = KeyReleased;
        inputEvent.key = event->key.code;
        isEvent = true;
    }

    if (event->type == sf::Event::MouseButtonPressed)
    {
        inputEvent.type = MouseClick;
        inputEvent.location.x = (float)event->mouseButton.x;
        inputEvent.location.y = (float)event->mouseButton.y;
        isEvent = true;
    }

    if (!isEvent) return;

    auto itr = m_objects.begin();
    while (itr != m_objects.end())
    {
        itr->second->HandleInput(&inputEvent);
        if (inputEvent.type == MouseClick)
        {
            if (itr->second->GetSprite()->getGlobalBounds().contains(inputEvent.location.x, inputEvent.location.y))
            {
                itr->second->OnMouseClickOnObject.Invoke();
            }
        }
        itr++;
    }
}

void ObjectManager::UpdateAll(float deltaTime)
{
    auto itr = m_objects.begin();
    while (itr != m_objects.end())
    {
        itr->second->Update(deltaTime);
        itr++;
    }

    // Detect Collision:

    auto originItr = m_objects.begin();
    while (originItr != m_objects.end())
    {
        sf::Rect<float> originBounds = originItr->second->GetSprite()->getGlobalBounds();

        auto targetItr = m_objects.begin();
        while (targetItr != m_objects.end())
        {
            sf::Rect<float> otherBounds = targetItr->second->GetSprite()->getGlobalBounds();

            if (originBounds.intersects(otherBounds))
            {
                originItr->second->OnCollidesWith(targetItr->second);
            }

            targetItr++;
        }

        originItr++;
    }
}

void ObjectManager::RenderAll(sf::RenderWindow *window)
{
    auto itr = m_objects.begin();
    while (itr != m_objects.end())
    {
        itr->second->Render(window);
        itr++;
    }
}
