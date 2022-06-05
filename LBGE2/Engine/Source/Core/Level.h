
#ifndef LBGE2_LEVEL_H
#define LBGE2_LEVEL_H

#include "../State/GameState.h"
#include "../Objects/ObjectManager.h"
#include "Map.h"

class Level
{
public:
    virtual ~Level();
    virtual void Init();
    virtual void UpdateLevel(float deltaTime);
    void UpdateLevel(sf::Time time);
    virtual void RenderLevel(sf::RenderWindow* window);
    virtual void RenderLevel(sf::RenderTexture* rtexture);
    virtual void HandleInput(sf::Event* event);

    void SetState(GameState* state);
    GameState* GetState();

    std::map<std::string, LBGEObject*>* GetAllObjectsInLevel() { return m_manager.GetAllObjects(); }
    void DestroyObject(const std::string& name) { m_manager.Remove(name); }
    void CreateObject(const std::string& name, LBGEObject* object);

    static Level* ConstructLevelFromFile(const std::string& filePath);
    void SaveCurrentLevelToFile(const std::string& filePath);

protected:
    GameState* m_state;
    Map* m_map;
    ObjectManager m_manager;

};


#endif //LBGE2_LEVEL_H
