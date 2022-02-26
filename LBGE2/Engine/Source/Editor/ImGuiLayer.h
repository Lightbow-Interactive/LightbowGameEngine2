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
    std::string m_openedLevelFile;

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

    bool m_createComponent = false;
    std::string m_componentName = "";
    std::string m_selectedComponentType = "";
    void CreateComponent();

};


#endif //LBGE2_IMGUILAYER_H
