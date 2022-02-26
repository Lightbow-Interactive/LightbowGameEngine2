#include <fstream>
#include <sstream>
#include "Level.h"
#include "Logger.h"
#include "../Objects/SerializedTypes.h"
#include "json/json_struct.h"

Level::~Level()
{
    delete m_state;
}

void Level::Init()
{
    if (!m_state) m_state = new GameState();
    m_state->Init();
}

void Level::UpdateLevel(float deltaTime)
{
    m_state->Update(deltaTime);
    m_manager.UpdateAll(deltaTime);
}

void Level::RenderLevel(sf::RenderWindow *window)
{
    m_state->Render(window);
    m_manager.RenderAll(window);
}

void Level::RenderLevel(sf::RenderTexture *rtexture)
{
    m_manager.RenderAll(rtexture);
}

void Level::HandleInput(sf::Event *event)
{
    m_state->HandleInput(event);
    m_manager.HandleInputAll(event);
}

void Level::SetState(GameState *state)
{
    m_state = state;
}

GameState *Level::GetState()
{
    return m_state;
}

Level* Level::ConstructLevelFromFile(const std::string& filePath)
{
    std::ifstream ifs(filePath);
    std::stringstream ifbuffer;

    ifbuffer << ifs.rdbuf();

    SerializedLevel thisLevel;
    JS::ParseContext context(ifbuffer.str());

    context.parseTo(thisLevel);

    return nullptr;
}

void Level::SaveCurrentLevelToFile(const std::string &filePath)
{
    Logger::Log("Saving level...");

    std::map<std::string, LBGEObject*>* allObjects = m_manager.GetAllObjects();
    SerializedLevel thisLevel;

    auto itr = allObjects->begin();
    while (itr != allObjects->end())
    {
        thisLevel.objects.emplace_back(SerializedLBGEObject(itr->first, itr->second));
        itr++;
    }

    std::string jsonLevel = JS::serializeStruct(thisLevel);

    std::ofstream ofs;
    ofs.open(filePath, std::ofstream::out | std::ofstream::trunc);

    ofs << jsonLevel;

    ofs.close();

    Logger::Log("Level saved. (" + filePath + ")");
}
