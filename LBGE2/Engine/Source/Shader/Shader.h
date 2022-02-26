#ifndef LBGE2_SHADER_H
#define LBGE2_SHADER_H

#include "SFML/Graphics.hpp"

class Shader
{
public:
    Shader();
    Shader(const std::string& vertexFile, const std::string& fragmentFile);

    void SetVertex(const std::string& vertexFile);
    void SetFragment(const std::string& fragmentFile);

    sf::Shader* GetShaderRef();
    const std::string* GetFragmentFile() { return &m_fragment; }
    const std::string* GetVertexFile() { return &m_vertex; }

    static void CheckAvail();
    static bool ISAVAIL;


private:
    std::string m_fragment;
    std::string m_vertex;
    sf::Shader m_shader;

};


#endif //LBGE2_SHADER_H
