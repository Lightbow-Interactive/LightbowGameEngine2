#ifndef LBGE2_IMGUILAYER_H
#define LBGE2_IMGUILAYER_H

#include "SFML/Graphics.hpp"

class ImGuiLayer
{
public:
    void Init(sf::RenderWindow& mainWindow);
    void ShutDown();

    void OnEvent(sf::RenderWindow& window, sf::Event& event);
    void Update(sf::RenderWindow& window, sf::Time& timeElapsed);
    void Render(sf::RenderWindow& window);

    void ProcessGui();

private:
    sf::RenderTexture* m_frameBuffer;
    int m_dockspaceId;

};


#endif //LBGE2_IMGUILAYER_H
