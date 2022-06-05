#include "Map.h"

Map::Map()
{
}

Map::Map(const std::string &mapFile)
{
    m_mapFile = mapFile;
    m_renderUpToLayer = 0;
}

Map::~Map()
{
    auto itr = m_layers.begin();
    while (itr != m_layers.end())
    {
        delete itr->second;
        itr++;
    }
}

void Map::Update(sf::Time time)
{
    if (m_renderUpToLayer < 1) return;

    auto itr = m_layers.begin();
    while (itr != m_layers.end())
    {
        if (itr->first <= m_renderUpToLayer)
        {
            itr->second->update(time);
        }
        else break;
    }
}

void Map::Render(sf::RenderTarget* rt)
{
    if (m_renderUpToLayer < 1) return;

    auto itr = m_layers.begin();
    while (itr != m_layers.end())
    {
        if (itr->first <= m_renderUpToLayer)
        {
            rt->draw(*itr->second);
        }
        else break;
    }
}

void Map::LoadMap()
{
    m_map.load(m_mapFile);
}

void Map::AddLayer(int layer)
{
    m_layers.insert(std::pair<int, MapLayer*>(layer, new MapLayer(m_map, layer)));
}

void Map::SetRenderUpToLayer(int layer)
{
    m_renderUpToLayer = layer;
}






