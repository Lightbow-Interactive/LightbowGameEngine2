#include "Shader.h"
#include <iostream>

bool Shader::ISAVAIL = true;

Shader::Shader() = default;

Shader::Shader(const std::string &vertexFile, const std::string &fragmentFile)
{
    if (!ISAVAIL) return;

    m_shader.loadFromFile(vertexFile, sf::Shader::Vertex);
    m_shader.loadFromFile(fragmentFile, sf::Shader::Fragment);
}

void Shader::SetVertex(const std::string &vertexFile)
{
    if (!ISAVAIL) return;

    m_shader.loadFromFile(vertexFile, sf::Shader::Vertex);
}

void Shader::SetFragment(const std::string &fragmentFile)
{
    if (!ISAVAIL) return;

    m_shader.loadFromFile(fragmentFile, sf::Shader::Fragment);
}

sf::Shader *Shader::GetShaderRef()
{
    if (ISAVAIL) return &m_shader;
    return nullptr;
}

void Shader::CheckAvail()
{
    if (!sf::Shader::isAvailable())
    {
        ISAVAIL = false;
        std::cout << "Shaders are not available on this system." << std::endl;
    }
}
