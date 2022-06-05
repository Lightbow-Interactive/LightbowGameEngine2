#ifndef LBGE2_IMGUILAYER_H
#define LBGE2_IMGUILAYER_H

#include "SFML/Graphics.hpp"
#include "../Objects/LBGEObject.h"
#include "ImGui/imgui.h"
#include "ImGui/imfilebrowser.h"

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
    ImGui::FileBrowser fileDialog;
    std::string m_openedLevelFile;

    sf::RenderTexture* m_frameBuffer;
    LBGEObject* m_selectedObject;
    std::string m_selectedObjectName;

    std::string m_contentRootPath;
    std::filesystem::path m_currentFileBrowserDir;
    sf::Texture m_contentBrowserFolderTexture;
    sf::Texture m_contentBrowserFileTexture;
    std::filesystem::path m_dragDropPathCurrent;

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
    
    bool m_createObject = false;
    void CreateObject();

};


#endif //LBGE2_IMGUILAYER_H
