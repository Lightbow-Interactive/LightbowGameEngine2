#ifndef LBGE2_LUASCRIPTCOMPONENT_H
#define LBGE2_LUASCRIPTCOMPONENT_H

#include "../ObjectComponent.h"
#include <iostream>

class LuaScriptComponent : public ObjectComponent
{
public:
    LuaScriptComponent(LBGEObject* owner);
    std::string* GetScriptName() { return &m_luaScript; }



private:
    std::string m_luaScript = "";

};


#endif //LBGE2_LUASCRIPTCOMPONENT_H
