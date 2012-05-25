#include "Platform.hpp"

Platform::Platform(b2World* world, float32 x, float32 y, float32 width, float32 height, std::string texturePath, bool isCloud) : StaticElement(world,x,y)
{
    texture.LoadFromFile(texturePath);
    texture.SetRepeated(true);
    sprite.SetTexture(texture);
    sprite.SetTextureRect(sf::IntRect(0,0,width*200,height*200));
    sprite.SetOrigin(sprite.GetLocalBounds().Width/2.0f,sprite.GetLocalBounds().Height/2.0f);

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


