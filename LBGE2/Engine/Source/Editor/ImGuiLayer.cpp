#include "ImGuiLayer.h"
#include "../../ImGui/imgui.h"
#include "../../ImGui/imgui-SFML.h"
#include "../../ImGui/imgui_internal.h"
#include <iostream>
#include "../Core/Game.h"
#include "../Core/Logger.h"
#include "../UserInterface/TextBlock.h"
#include "../UserInterface/Fonts.h"

void ImGuiLayer::Init(sf::RenderWindow& window)
{
    Logger::Log("Initializing editor...");

    m_frameBuffer = Game::GetRenderFrameBuffer();

    //ImGui::SFML::Init(window);
    ImGui::SFML::Init(window);
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetStyle().ScaleAllSizes(2);

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("Resources/Poppins-Regular.ttf", 30);
    ImGui::SFML::UpdateFontTexture();
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
    ViewportWindow();
    PropertiesWindow();
    LogWindow();
    ContentWindow();
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
                                                            0.2f, nullptr,
                                                            &dockspace_id);
            auto dock_id_right = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right,
                                                             0.25f, nullptr,
                                                             &dockspace_id);
            auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down,
                                                            0.2f, nullptr,
                                                            &dockspace_id);

            ImGui::DockBuilderDockWindow("Viewport", dock_id_center);
            ImGui::DockBuilderDockWindow("Level", dock_id_left);
            ImGui::DockBuilderDockWindow("Properties", dock_id_right);
            ImGui::DockBuilderDockWindow("Log", dock_id_down);
            ImGui::DockBuilderDockWindow("Content", dock_id_down);
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
            if (ImGui::MenuItem("Open ..."))
            {
                // todo: open
            }
            if (ImGui::MenuItem("Save"))
            {
                // todo: save
            }
            if (ImGui::MenuItem("Close"))
            {
                // todo: close
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
            }
            if (ImGui::MenuItem("Reset"))
            {
                Game::ResetGameEditor();
                // todo: reset to startup level
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Create"))
        {
            if (ImGui::BeginMenu("Objects"))
            {
                if (ImGui::MenuItem("LBGEObject"))
                {
                    // todo: create object
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
                    // todo: add component
                }
                if (ImGui::MenuItem("Duplicate"))
                {
                    // todo: duplicate
                }
                if (ImGui::MenuItem("Delete"))
                {
                    // todo: delete
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

    int selected = 0;

    auto itr = objectsInLevel->begin();
    while (itr != objectsInLevel->end())
    {
        if (ImGui::Selectable(itr->first.c_str()))
        {
            m_selectedObjectName = itr->first;
            m_selectedObject = itr->second;
        }
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
    ImGui::Begin("Content");
    ImGui::Text("This is the content window");
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
            if (ImGui::InputFloat("X", &posX))
            {
                position.x = posX;
                m_selectedObject->SetPosition(position);
            }
            ImGui::SameLine();
            if (ImGui::InputFloat("Y", &posY))
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
            if (ImGui::InputFloat("X", &scaleX))
            {
                scale.x = scaleX;
                m_selectedObject->SetScale(scale);
            }
            ImGui::SameLine();
            if (ImGui::InputFloat("Y", &scaleY))
            {
                scale.y = scaleY;
                m_selectedObject->SetScale(scale);
            }
            ImGui::PopItemWidth();

            ImGui::TreePop();
        }

        if (dynamic_cast<TextBlock*>(m_selectedObject))
        {
            TextBlock* textBlock = static_cast<TextBlock*>(m_selectedObject);

            if (ImGui::TreeNode("Text Options"))
            {
                // todo: fix text input

                ImGui::Text("Text: ");
                ImGui::SameLine();

                char buff[255]{};
                strcpy(buff, textBlock->GetText().c_str());
                ImGui::InputText("", buff, IM_ARRAYSIZE(buff));
                {
                    textBlock->SetText(buff);
                }

                ImGui::Text("Size:  ");
                ImGui::SameLine();
                ImGui::PushItemWidth(200);
                int fontSize = textBlock->GetFontSize();
                if (ImGui::InputInt("", &fontSize))
                {
                    textBlock->SetFontSize(fontSize);
                }
                ImGui::PopItemWidth();

                // todo: fix font input

                ImGui::Text("Font: ");
                ImGui::SameLine();
                ImGui::PushItemWidth(200);
                char fontbuff[255]{};
                strcpy(buff, Fonts::GetFontName(const_cast<sf::Font *>(textBlock->GetFont())).c_str());
                if (ImGui::InputText("", fontbuff, IM_ARRAYSIZE(fontbuff)))
                {
                    textBlock->SetFont(fontbuff);
                }

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
                    ImGui::Selectable(itr->first.c_str());
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

