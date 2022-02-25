#include "ObjectComponent.h"
#include "../LBGEObject.h"

ObjectComponent::ObjectComponent(LBGEObject *owner)
{
    m_owner = owner;
}

void ObjectComponent::Init()
{
}

void ObjectComponent::UpdateComponent(float deltaTime)
{
}



