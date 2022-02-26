#ifndef LBGE2_SERIALIZEDTYPES_H
#define LBGE2_SERIALIZEDTYPES_H

#include <string>
#include "SFML/Graphics.hpp"
#include <vector>
#include "../Types/Vector.h"
#include "../Shader/Shader.h"
#include "../Core/Level.h"
#include "../Objects/LBGEObject.h"
#include "../Objects/Components/ObjectComponent.h"
#include "json/json_struct.h"

struct SerializedVector2f
{
    float x;
    float y;

    SerializedVector2f() {};
    SerializedVector2f(sf::Vector2f vector)
    {
        x = vector.x;
        y = vector.y;
    }
    SerializedVector2f(Vector2<float> vector)
    {
        x = vector.x;
        y = vector.y;
    }
};
JS_OBJ_EXT(SerializedVector2f, x, y);

struct SerializedShader
{
    std::string vertex;
    std::string fragment;

    SerializedShader() {}
    SerializedShader(Shader* shader)
    {
        if (!shader) return;
        vertex = *shader->GetVertexFile();
        fragment = *shader->GetFragmentFile();
    }
};
JS_OBJ_EXT(SerializedShader, vertex, fragment);

struct SerializedObjectComponent
{
    // todo: components
    int placeholder;

    SerializedObjectComponent() { placeholder = 1; }
};
JS_OBJ_EXT(SerializedObjectComponent, placeholder);

struct SerializedLBGEObject
{
    std::string name;
    std::string textureFile;
    SerializedVector2f position;
    float rotation;
    SerializedVector2f scale;
    SerializedShader shader;
    std::vector<SerializedObjectComponent> components;

    SerializedLBGEObject() {}
    SerializedLBGEObject(const std::string& _name, LBGEObject* object)
    {
        if (!object) return;
        name = _name;
        textureFile = *object->GetTextureFile();
        position = SerializedVector2f(object->GetPosition());
        rotation = object->GetRotation();
        scale = SerializedVector2f(object->GetScale());
        shader = SerializedShader(object->GetShader());
        // todo: components
    }
};
JS_OBJ_EXT(SerializedLBGEObject, name, textureFile, position, rotation, scale, shader, components);

struct SerializedLevel
{
    std::vector<SerializedLBGEObject> objects;

    SerializedLevel() {}
};
JS_OBJ_EXT(SerializedLevel, objects);

#endif //LBGE2_SERIALIZEDTYPES_H
