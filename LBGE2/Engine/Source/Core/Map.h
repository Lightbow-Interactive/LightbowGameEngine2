#ifndef LBGE2_MAP_H
#define LBGE2_MAP_H

#include <string>
#include "tmxlite/Map.hpp"
#include "tmxlite/SFMLOrthogonalLayer.hpp"

class Map
{
public:
    Map();
    explicit Map(const std::string& mapFile);
    ~Map();

    void Update(sf::Time time);
    void Render(sf::RenderTarget* rt);

    void LoadMap();
    void AddLayer(int layer);
    void SetRenderUpToLayer(int layer);

private:
    std::string m_mapFile;
    tmx::Map m_map;
    std::map<int, MapLayer*> m_layers;
    int m_renderUpToLayer;

};


#endif //LBGE2_MAP_H
