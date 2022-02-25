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

    static void CheckAvail();
    static bool ISAVAIL;


private:
    sf::Shader m_shader;

};


#endif //LBGE2_SHADER_H
