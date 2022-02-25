#ifndef LBGE2_OBJECTCOMPONENT_H
#define LBGE2_OBJECTCOMPONENT_H

class LBGEObject;

class ObjectComponent
{
public:
    explicit ObjectComponent(LBGEObject* owner);
    virtual void Init();
    virtual void UpdateComponent(float deltaTime);

protected:
    LBGEObject* m_owner;

};


#endif //LBGE2_OBJECTCOMPONENT_H
