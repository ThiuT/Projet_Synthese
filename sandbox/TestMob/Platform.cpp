#include "Platform.hpp"

Platform::Platform(b2World* world, float32 x, float32 y, float32 width, float32 height) : StaticElement(world,x,y)
{
    box.SetAsBox(width,height);
    fixturedef.shape = &box;
    fixturedef.density = 1.0f;
    fixturedef.friction = 2.0f;
    body->CreateFixture(&fixturedef);

    ID = "PLATFORM";
    body->SetUserData(this);
}
