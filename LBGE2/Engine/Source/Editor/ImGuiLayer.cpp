#include "ImGuiLayer.h"
#include "../../ImGui/imgui.h"
#include "../../ImGui/imgui-SFML.h"
#include "../../ImGui/imgui_internal.h"
#include <iostream>
#include "../Core/Game.h"

void ImGuiLayer::Init(sf::RenderWindow& window)
{
    std::cout << "Initializing Editor..." << std::endl;

    m_frameBuffer = Game::GetRenderFrameBuffer();
    m_dockspaceId = 0;

    //ImGui::SFML::Init(window);
    ImGui::SFML::Init(window);
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetStyle().ScaleAllSizes(2);
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
    /*if (ImGui::Begin("LBGE Editor", nullptr, ImGuiWindowFlags_MenuBar))
    {
        ImGui::SetWindowPos(ImVec2(0, 0));
        ImGui::SetWindowSize(ImVec2((float)Game::SCREEN_WIDTH*2, (float)Game::SCREEN_HEIGHT*2));

        //m_dockspaceId = (int)ImGui::GetID("HUB_DockSpace");

        //ImGui::DockSpace(m_dockspaceId, ImVec2(0, 0), ImGuiDockNodeFlags_None|ImGuiDockNodeFlags_PassthruCentralNode);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New"))
                {

                }
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    ImGui::End();*/




    //ImGui::SetNextWindowDockID(m_dockspaceId, ImGuiCond_FirstUseEver);
    ImGui::Begin("GameWindow");
    {
        ImGui::BeginChild("GameRenderer");
        ImGui::Image(*m_frameBuffer, (ImVec2)m_frameBuffer->getSize());
        ImGui::EndChild();
    }
    ImGui::End();

    //ImGui::SetNextWindowDockID(m_dockspaceId);
    ImGui::Begin("Level");
    {
        ImGui::Text("Hi");
    }
    ImGui::End();

    //ImGui::SetNextWindowDockID(m_dockspaceId);
    ImGui::Begin("Log");
    {
        ImGui::Text("Log");
    }
    ImGui::End();
}
