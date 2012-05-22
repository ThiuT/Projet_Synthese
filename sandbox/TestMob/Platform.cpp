#include "Platform.hpp"

Platform::Platform(b2World* world, float32 x, float32 y, float32 width, float32 height, bool isCloud) : StaticElement(world,x,y)
{
    box.SetAsBox(width,height);
    fixturedef.shape = &box;
    fixturedef.density = 1.0f;
    fixturedef.friction = 1.0f;
    body->CreateFixture(&fixturedef);

    cloud = isCloud;
    body->SetUserData(this);
}

bool Platform::IsCloud()
{
    return cloud;
}


