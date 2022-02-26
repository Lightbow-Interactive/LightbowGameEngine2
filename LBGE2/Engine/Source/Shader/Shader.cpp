#include "Shader.h"
#include "../Core/Logger.h"
#include <iostream>

bool Shader::ISAVAIL = true;

Shader::Shader() = default;

Shader::Shader(const std::string &vertexFile, const std::string &fragmentFile)
{
    if (!ISAVAIL) return;

    m_shader.loadFromFile(vertexFile, sf::Shader::Vertex);
    m_shader.loadFromFile(fragmentFile, sf::Shader::Fragment);

    m_fragment = fragmentFile;
    m_vertex = vertexFile;
}

void Shader::SetVertex(const std::string &vertexFile)
{
    if (!ISAVAIL) return;

    m_shader.loadFromFile(vertexFile, sf::Shader::Vertex);

    m_vertex = vertexFile;
}

void Shader::SetFragment(const std::string &fragmentFile)
{
    if (!ISAVAIL) return;

    m_shader.loadFromFile(fragmentFile, sf::Shader::Fragment);

    m_fragment = fragmentFile;
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
        Logger::Error("Shaders are not available on this system.");
    }
}
