#include "InteractiveDecor.hpp"

 InteractiveDecor::InteractiveDecor(b2World* world, float32 x, float32 y, float32 width, float32 height, int type) : StaticElement(world,x,y)
{
    switch(type) {
        case LADDER:
            texture.LoadFromFile("Ladder.png");
            texture.SetRepeated(true);
            sprite.SetTexture(texture);
            sprite.SetTextureRect(sf::IntRect(0,0,texture.GetWidth(),height*100));
            sprite.SetOrigin(sprite.GetLocalBounds().Width/2.0f,sprite.GetLocalBounds().Height/2.0f);
            ID = "LADDER";
            break;
        default:
            break;
    }

    box.SetAsBox(sprite.GetLocalBounds().Width/200.0f,sprite.GetLocalBounds().Height/200.0f);
    fixturedef.shape = &box;
    fixturedef.density = 1.0f;
    fixturedef.isSensor = true;
    body->CreateFixture(&fixturedef);
    body->SetUserData(this);
}

