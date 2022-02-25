#ifndef LBGE2_IMGUILAYER_H
#define LBGE2_IMGUILAYER_H

#include "SFML/Graphics.hpp"
#include "../Objects/LBGEObject.h"

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
    LBGEObject* m_selectedObject;
    std::string m_selectedObjectName;

    void MainLayout();
    void MainMenuBar();
    void LevelWindow();
    void LogWindow();
    void ContentWindow();
    void ViewportWindow();
    void PropertiesWindow();

};


#endif //LBGE2_IMGUILAYER_H
