#include "ImGuiLayer.h"
#include "ImGui/imgui-SFML.h"
#include "ImGui/imgui_internal.h"
#include <iostream>
#include "../Core/Game.h"
#include "../Core/Logger.h"
#include "../UserInterface/TextBlock.h"
#include "../UserInterface/Fonts.h"
#include "../Objects/Components/DefaultComponents/CppScriptComponent.h"
#include "../Objects/Components/DefaultComponents/LuaScriptComponent.h"
#include "../Objects/Components/DefaultComponents/PhysicsComponent.h"

void ImGuiLayer::Init(sf::RenderWindow& window)
{
    Logger::Log("Initializing editor...");

    m_contentRootPath = "/Users/pascalgluth/Desktop/LightbowGameEngine2/LBGE2/PongTemplate/Resources";
    m_currentFileBrowserDir = m_contentRootPath;
    Logger::Log("Project content directory is " + m_contentRootPath);

    if (!m_contentBrowserFileTexture.loadFromFile("Resources/Editor/file_icon.png") ||
        !m_contentBrowserFolderTexture.loadFromFile("Resources/Editor/folder_icon.png"))
    {
        Logger::Error("Failed to load content browser icons");
    }

    m_frameBuffer = Game::GetRenderFrameBuffer();

    //ImGui::SFML::Init(window);
    if (!ImGui::SFML::Init(window)) return;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetStyle().ScaleAllSizes(2);

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("Resources/Poppins-Regular.ttf", 30);
    if (!ImGui::SFML::UpdateFontTexture()) return;

    fileDialog.SetTitle("Select Level");
    fileDialog.SetTypeFilters({".lbgelvl"});
}

void ImGuiLayer::ShutDown()
{
    std::cout << "Shutting down editor..." << std::endl;
    ImGui::SFML::Shutdown();
}

void ImGuiLayer::OnEvent(sf::RenderWindow& window, sf::Event& event)
{
    ImGui::SFML::ProcessEvent(window, event);
}

void ImGuiLayer::Update(sf::RenderWindow& window, sf::Time& timeElapsed)
{
    ImGui::SFML::Update(window, timeElapsed);
}

void ImGuiLayer::Render(sf::RenderWindow& window)
{
    ImGui::SFML::Render(window);
}

void ImGuiLayer::ProcessGui()
{
    MainLayout();
    MainMenuBar();
    LevelWindow();
    PropertiesWindow();
    LogWindow();
    ContentWindow();
    ViewportWindow();

    if (m_createComponent) CreateComponent();
    if (m_createObject) CreateObject();
}

void ImGuiLayer::MainLayout()
{
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("LBGE Editor", nullptr, window_flags);
    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("DockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        static auto first_time = true;
        if (first_time)
        {
            first_time = false;

            ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
            ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
            ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

            auto dock_id_center = dockspace_id;
            auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left,
                                                            0.19f, nullptr,
                                                            &dockspace_id);
            auto dock_id_right = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right,
                                                             0.25f, nullptr,
                                                             &dockspace_id);
            auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down,
                                                            0.25f, nullptr,
                                                            &dockspace_id);

            ImGui::DockBuilderDockWindow("Level", dock_id_left);
            ImGui::DockBuilderDockWindow("Properties", dock_id_right);
            ImGui::DockBuilderDockWindow("Log", dock_id_down);
            ImGui::DockBuilderDockWindow("Content", dock_id_down);
            ImGui::DockBuilderDockWindow("Viewport", dock_id_center);
            ImGui::DockBuilderFinish(dockspace_id);
        }
    }
    ImGui::End();
}

void ImGuiLayer::MainMenuBar()
{
    ImGui::BeginMainMenuBar();
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open Level ..."))
            {
                // todo: open

                fileDialog.Open();

                /*nfdchar_t* outPath = NULL;
                nfdresult_t result = NFD_OpenDialog("lbgelvl", NULL, &outPath);

                if (result == NFD_OKAY)
                {
                    m_openedLevelFile = outPath;
                    delete outPath;
                    Logger::Log("Opening " + m_openedLevelFile + " ...");

                    Level* newLevel = Level::ConstructLevelFromFile(m_openedLevelFile);
                    if (newLevel) Game::ChangeLevel(newLevel);
                    else
                    {
                        m_openedLevelFile = "";
                        Game::ChangeLevel(new Level());
                        Logger::Error("Failed to load level.");
                    }
                }
                else
                {
                    Logger::Log("Open Canceled");
                }*/
            }
            if (ImGui::MenuItem("Save"))
            {
                Level* level = Game::GetLevel();
                if (level)
                {
                    level->SaveCurrentLevelToFile(m_openedLevelFile);
                }
            }
            if (ImGui::MenuItem("Close"))
            {
                m_openedLevelFile = "";
                Game::ChangeLevel(new Level());
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Game"))
        {
            if (ImGui::MenuItem("Start"))
            {
                Game::SetGameRunningEditor(true);
            }
            if (ImGui::MenuItem("Stop"))
            {
                Game::SetGameRunningEditor(false);
                // todo: reset level to defaults
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Create"))
        {
            if (ImGui::BeginMenu("Objects"))
            {
                if (ImGui::MenuItem("LBGEObject"))
                {
                    m_createObject = true;
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("User Interface"))
            {
                if (ImGui::MenuItem("TextBlock"))
                {
                    // todo: create textblock
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (m_selectedObject)
        {
            if (ImGui::BeginMenu("Selected Object"))
            {
                if (ImGui::MenuItem("Add Component"))
                {
                    m_createComponent = true;
                }
                if (ImGui::MenuItem("Unselect"))
                {
                    m_selectedObjectName = "";
                    m_selectedObject = nullptr;
                }
                if (ImGui::MenuItem("Delete"))
                {
                    Logger::Log("Deleting object " + m_selectedObjectName + "...");

                    Level* level = Game::GetLevel();
                    if (level)
                    {
                        level->DestroyObject(m_selectedObjectName);
                        m_selectedObjectName = "";
                        m_selectedObject = nullptr;
                    }
                }

                ImGui::EndMenu();
            }
        }

        ImGui::SetCursorPosX(ImGui::GetWindowWidth()-85);
        ImGui::Text("FPS: %d", Game::LAST_FPS);

        ImGui::SetCursorPosX(ImGui::GetWindowWidth()-200);
        if (Game::IsGameRunningEditor()) ImGui::Text("Running");
        else ImGui::Text("Paused");
    }
    ImGui::EndMainMenuBar();

    fileDialog.Display();

    if (fileDialog.HasSelected())
    {
        m_openedLevelFile = fileDialog.GetSelected().string();
        Logger::Log("Opening " + m_openedLevelFile + " ...");

        Level* newLevel = Level::ConstructLevelFromFile(m_openedLevelFile);
        if (newLevel) Game::ChangeLevel(newLevel);
        else
        {
            m_openedLevelFile = "";
            Game::ChangeLevel(new Level());
            Logger::Error("Failed to load level.");
        }

        fileDialog.ClearSelected();
    }
}

void ImGuiLayer::LevelWindow()
{
    ImGui::Begin("Level");
    ImGui::LabelText("", "Objects in Level");

    Level* level = Game::GetLevel();
    if (!level)
    {
        ImGui::Text("Error loading objects in level");
        ImGui::End();
        return;
    }

    std::map<std::string, LBGEObject*>* objectsInLevel = level->GetAllObjectsInLevel();

    ImGui::Indent();
    
    auto itr = objectsInLevel->begin();
    while (itr != objectsInLevel->end())
    {
        bool isSelected = (itr->first == m_selectedObjectName);
        if (ImGui::Selectable(itr->first.c_str(), isSelected))
        {
            m_selectedObjectName = itr->first;
            m_selectedObject = itr->second;
        }
        if (isSelected) itr->second->SetEditorDrawOutline(true);
        else itr->second->SetEditorDrawOutline(false);
        ImGui::SetItemDefaultFocus();
        itr++;
    }

    ImGui::Unindent();

    ImGui::End();
}

void ImGuiLayer::LogWindow()
{
    ImGui::Begin("Log");
    ImGui::Text("%s", Logger::GetLog().c_str());
    ImGui::End();
}

void ImGuiLayer::ContentWindow()
{
    ImGui::Begin("Content Browser");

    //float columns = ImGui::GetWindowWidth()/200;

    float padding = 512.f*10.f/150.f;
    static float thumbnailSize = 150;
    float itemSize = thumbnailSize + padding;

    float panelWidth = ImGui::GetContentRegionAvail().x;
    int columns = (int)(panelWidth / itemSize);

    if (columns < 1)
    {
        ImGui::End();
        return;
    }

    if (m_currentFileBrowserDir != std::filesystem::path(m_contentRootPath))
    {
        if (ImGui::Button("<-"))
        {
            m_currentFileBrowserDir = m_currentFileBrowserDir.parent_path();
        }
    }

    ImGui::Columns(columns);

    for (auto& dir : std::filesystem::directory_iterator(m_currentFileBrowserDir))
    {
        auto relativePath = std::filesystem::relative(dir.path().filename(), m_contentRootPath);
        std::string filename = relativePath.filename().string();

        if (dir.is_directory())
            ImGui::ImageButton(m_contentBrowserFolderTexture,
                               {thumbnailSize, thumbnailSize+thumbnailSize/10});
        else
            ImGui::ImageButton(m_contentBrowserFileTexture,
                               {thumbnailSize, thumbnailSize+thumbnailSize/10});

        if (dir.is_directory() && ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            m_currentFileBrowserDir /= dir.path().filename();

        if (!dir.is_directory())
        {
            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
            {
                m_dragDropPathCurrent = dir;
                ImGui::SetDragDropPayload("file", &relativePath, sizeof(relativePath));
                ImGui::EndDragDropSource();
            }
        }

        ImGui::Text("%s", filename.c_str());

        ImGui::NextColumn();
    }

    ImGui::Columns(1);

    if (ImGui::SliderFloat("Size", &thumbnailSize, 64, 512))
        padding = (512*10)/thumbnailSize;

    ImGui::End();
}

void ImGuiLayer::ViewportWindow()
{
    ImGui::Begin("Viewport");
    {
        ImGui::BeginChild("GameRenderer");
        if (m_frameBuffer) ImGui::Image(*m_frameBuffer, (ImVec2)m_frameBuffer->getSize());
        ImGui::EndChild();
    }
    ImGui::End();
}

void ImGuiLayer::PropertiesWindow()
{
    ImGui::Begin("Properties");
    

    if (m_selectedObject)
    {
        ImGui::Text("Selected: %s", m_selectedObjectName.c_str());

        if (ImGui::TreeNode("Transform"))
        {
            ImGui::Text("Position:  ");
            ImGui::SameLine();
            Vector2<float> position = m_selectedObject->GetPosition();
            float posX = position.x;
            float posY = position.y;
            ImGui::PushItemWidth(100);
            if (ImGui::InputFloat("posX", &posX))
            {
                position.x = posX;
                m_selectedObject->SetPosition(position);
            }
            ImGui::SameLine();
            if (ImGui::InputFloat("posY", &posY))
            {
                position.y = posY;
                m_selectedObject->SetPosition(position);
            }
            ImGui::PopItemWidth();

            ImGui::Text("Rotation: ");
            ImGui::SameLine();
            float rotation = m_selectedObject->GetRotation();
            ImGui::PushItemWidth(200);
            if (ImGui::InputFloat("Angle", &rotation))
            {
                m_selectedObject->SetRotation(rotation);
            }
            ImGui::PopItemWidth();

            ImGui::Text("Scale:       ");
            ImGui::SameLine();
            Vector2<float> scale = m_selectedObject->GetScale();
            float scaleX = scale.x;
            float scaleY = scale.y;
            ImGui::PushItemWidth(100);
            if (ImGui::InputFloat("scX", &scaleX))
            {
                scale.x = scaleX;
                m_selectedObject->SetScale(scale);
            }
            ImGui::SameLine();
            if (ImGui::InputFloat("scY", &scaleY))
            {
                scale.y = scaleY;
                m_selectedObject->SetScale(scale);
            }
            ImGui::PopItemWidth();

            ImGui::TreePop();
        }
        
        if (ImGui::TreeNode("Sprite"))
        {
            ImGui::Text("Texture: ");
            ImGui::SameLine();
            ImGui::PushItemWidth(200);
            char buff[255]{};
            strcpy(buff, m_selectedObject->GetTextureFile()->c_str());
            if (ImGui::InputText("##spriteTexture", buff, IM_ARRAYSIZE(buff)))
            if (ImGui::BeginDragDropTarget())
            {
                if (ImGui::AcceptDragDropPayload("file"))
                {
                    Logger::Log("Setting texture to: " + std::string(m_dragDropPathCurrent));
                    m_selectedObject->SetTexture(m_dragDropPathCurrent.string());
                    m_dragDropPathCurrent = std::filesystem::path();
                }
                ImGui::EndDragDropTarget();
            }
            ImGui::PopItemWidth();
            
            
            ImGui::TreePop();
        }

        if (dynamic_cast<TextBlock*>(m_selectedObject))
        {
            auto* textBlock = dynamic_cast<TextBlock*>(m_selectedObject);

            if (ImGui::TreeNode("Text Options"))
            {
                ImGui::Text("Text: ");
                ImGui::SameLine();
                ImGui::PushItemWidth(200);
                char buff[255]{};
                strcpy(buff, textBlock->GetText().c_str());
                ImGui::InputText("max 255", buff, IM_ARRAYSIZE(buff));
                {
                    textBlock->SetText(buff);
                }
                ImGui::PopItemWidth();

                ImGui::Text("Size:  ");
                ImGui::SameLine();
                ImGui::PushItemWidth(200);
                int fontSize = textBlock->GetFontSize();
                if (ImGui::InputInt("px", &fontSize, 1, 10))
                {
                    if (fontSize < 1) fontSize = 1;
                    textBlock->SetFontSize(fontSize);
                }
                ImGui::PopItemWidth();

                // todo: fix font input

                ImGui::Text("Font: ");
                ImGui::SameLine();
                ImGui::PushItemWidth(200);

                char fontbuff[255]{};
                strcpy(buff, textBlock->GetFontFile()->c_str());
                ImGui::InputText("##fontDragDropFile", fontbuff, IM_ARRAYSIZE(fontbuff));
                if (ImGui::BeginDragDropTarget())
                {
                    if (ImGui::AcceptDragDropPayload("file"))
                    {
                        textBlock->SetFontByFile(m_dragDropPathCurrent.string());
                        m_dragDropPathCurrent = std::filesystem::path();
                    }
                    ImGui::EndDragDropTarget();
                }
                ImGui::PopItemWidth();

                ImGui::TreePop();
            }
        }

        if (ImGui::TreeNode("Components"))
        {
            std::map<std::string, ObjectComponent*>* components = m_selectedObject->GetComponents();
            if (components)
            {
                auto itr = components->begin();
                while (itr != components->end())
                {
                    if (ImGui::TreeNode(itr->first.c_str()))
                    {
                        if (dynamic_cast<LuaScriptComponent*>(itr->second))
                        {
                            auto* luaScriptComponent = dynamic_cast<LuaScriptComponent*>(itr->second);

                            ImGui::Text("Script: ");
                            ImGui::SameLine();
                            ImGui::PushItemWidth(200);
                            char scriptNameBuff[255]{};
                            strcpy(scriptNameBuff, luaScriptComponent->GetScriptName()->c_str());
                            if (ImGui::InputText("##luaScriptName", scriptNameBuff,
                                                 IM_ARRAYSIZE(scriptNameBuff)))
                            {
                                *luaScriptComponent->GetScriptName() = scriptNameBuff;
                            }
                            ImGui::PopItemWidth();
                        }
                        
                        if (dynamic_cast<PhysicsComponent*>(itr->second))
                        {
                            auto* physicsComponent = dynamic_cast<PhysicsComponent*>(itr->second);
                            
                            ImGui::Text("Physics Options...");
                        }
                        
                        ImGui::TreePop();
                    }
                    if (ImGui::BeginPopupContextItem("ComponentContextItem"))
                    {
                        if (ImGui::Selectable("Delete"))
                        {
                            m_selectedObject->RemoveComponent(itr->first);
                        }
                        ImGui::EndPopup();
                    }
                    itr++;
                }
            }
            else
            {
                ImGui::Text("Failed to load components.");
            }

            ImGui::TreePop();
        }

    }

    ImGui::End();
}

void ImGuiLayer::CreateComponent()
{
    if (!m_selectedObject) return;

    ImGui::Begin("Create Component");
    {
        ImGui::Text("Name: ");
        ImGui::SameLine();
        char buffName[255]{};
        if (!m_componentName.empty()) strcpy(buffName, m_componentName.c_str());
        if (ImGui::InputText("##componentName", buffName, IM_ARRAYSIZE(buffName)))
        {
            m_componentName = buffName;
        }

        ImGui::Text("Type:   ");
        ImGui::SameLine();

        const char* listbox_items[] = { "Lua Script", "Physics Component" };
        const char* selectedItem = "";

        if (!m_selectedComponentType.empty()) selectedItem = m_selectedComponentType.c_str();

        //ImGui::Indent();
        //ImGui::ListBox("##listBox1", &listBoxCurrentSelection, listbox_items,
        //               IM_ARRAYSIZE(listbox_items));

        if (ImGui::BeginCombo("##comboComponent", selectedItem))
        {
            for (auto & listbox_item : listbox_items)
            {
                bool isSelected = (selectedItem == listbox_item);
                if (ImGui::Selectable(listbox_item, isSelected)) selectedItem = listbox_item;
                if (isSelected) ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        //ImGui::Unindent();

        m_selectedComponentType = selectedItem;

        if (ImGui::Button("Create"))
        {
            if (m_selectedComponentType.empty() || m_componentName.empty()) return;

            Logger::Log("Creating component '" + m_componentName + "' of type " + m_selectedComponentType + "...");

            if (m_selectedComponentType == "C++ Script")
            {
                m_selectedObject->CreateComponent<CppScriptComponent>(m_componentName);
            }
            if (m_selectedComponentType == "Lua Script")
            {
                m_selectedObject->CreateComponent<LuaScriptComponent>(m_componentName);
            }
            if (m_selectedComponentType == "Physics Component")
            {
                m_selectedObject->CreateComponent<PhysicsComponent>(m_componentName);
            }

            m_selectedComponentType = "";
            m_componentName = "";
            m_createComponent = false;
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel"))
        {
            m_selectedComponentType = "";
            m_componentName = "";
            m_createComponent = false;
        }
    }
    ImGui::End();
}

void ImGuiLayer::CreateObject()
{
    ImGui::Begin("Create LBGEObject");
    {
        ImGui::Text("Name: ");
        ImGui::SameLine();
        static char buffObjName[255]{};
        ImGui::InputText("##newObjectName", buffObjName, IM_ARRAYSIZE(buffObjName));

        ImGui::Text("Texture: ");
        ImGui::SameLine();
        static char buffTexName[255]{};
        ImGui::InputText("##newObjectTexture", buffTexName, IM_ARRAYSIZE(buffTexName));
        
        if (ImGui::Button("Create"))
        {
            Level* level = Game::GetLevel();
            if (!level)
            {
                ImGui::End();
                return;
            }
            
            Logger::Log("Creating new object " + std::string(buffObjName) + " texture " + std::string(buffTexName));
            
            LBGEObject* newobject = new LBGEObject(std::string(buffTexName));
            level->CreateObject(std::string(buffObjName), newobject);
            
            m_createObject = false;
        }
        
        ImGui::SameLine();
        
        if (ImGui::Button("Cancel"))
        {
            m_createObject = false;
        }
        
    }
    ImGui::End();
}
