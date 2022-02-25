#ifndef LBGE2_GAME_H
#define LBGE2_GAME_H

#include "SFML/Graphics.hpp"
#include "Level.h"
#include "../Editor/ImGuiLayer.h"

class Game
{
public:
    static int WIDTH;
    static int HEIGHT;
    static std::string WINDOW_NAME;
    static int FRAMERATE_LIMIT;
    static int LAST_FPS;

    static void Start();
    static void StartEditor();
    static void GameLoop();
    static void GameLoopEditor();

    static void SetStartupLevel(Level* level);
    static void ChangeLevel(Level* level);
    static Level* GetLevel();

    static sf::RenderTexture* GetRenderFrameBuffer() { return &m_frameBuffer; };
    static void SetGameRunningEditor(bool newVal) { m_editorGameRunning = newVal; }
    static bool IsGameRunningEditor() { return m_editorGameRunning; };
    static void ResetGameEditor();

private:
    static sf::RenderWindow m_window;
    static sf::Clock m_clock;
    static Level* m_level;
    static sf::Image m_icon;

    static bool m_editorGameRunning;
    static ImGuiLayer m_imGuiLayer;
    static sf::RenderTexture m_frameBuffer;

};


#endif //LBGE2_GAME_H
