#ifndef LBGE2_OBJECTCOMPONENT_H
#define LBGE2_OBJECTCOMPONENT_H

#include <string>

class LBGEObject;

class ObjectComponent
{
public:
    explicit ObjectComponent(LBGEObject* owner);
    virtual void Init();
    virtual void UpdateComponent(float deltaTime);

    virtual std::string GetSerializedSaveFile() { return ""; };

protected:
    LBGEObject* m_owner;

};


#endif //LBGE2_OBJECTCOMPONENT_H
