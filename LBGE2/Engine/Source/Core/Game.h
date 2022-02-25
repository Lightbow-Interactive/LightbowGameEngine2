#ifndef LBGE2_GAME_H
#define LBGE2_GAME_H

#include "SFML/Graphics.hpp"
#include "Level.h"
#include "../Editor/ImGuiLayer.h"

class Game
{
public:
    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;
    static std::string WINDOW_NAME;
    static int FRAMERATE_LIMIT;

    static void Start();
    static void GameLoop();

    static void SetLevel(Level* level);
    static Level* GetLevel();

    static sf::RenderTexture* GetRenderFrameBuffer() { return &m_frameBuffer; };

private:
    static sf::RenderWindow m_window;
    static sf::Clock m_clock;
    static Level* m_level;
    static sf::Image m_icon;

    static bool m_editor;
    static ImGuiLayer m_imGuiLayer;
    static sf::RenderTexture m_frameBuffer;

};


#endif //LBGE2_GAME_H
