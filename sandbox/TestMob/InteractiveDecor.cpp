#include "InteractiveDecor.hpp"

 InteractiveDecor::InteractiveDecor(b2World* world, float32 x, float32 y, float32 width, float32 height, int t) : StaticElement(world,x,y)
{
    type = t;
    switch(type) {
        case LADDER:
            texture.LoadFromFile("Ladder.png");
            texture.SetRepeated(true);
            sprite.SetTexture(texture);
            sprite.SetTextureRect(sf::IntRect(0,0,texture.GetWidth(),height*200));
            sprite.SetOrigin(sprite.GetLocalBounds().Width/2.0f,sprite.GetLocalBounds().Height/2.0f);
            ID = "LADDER";
            break;
        case FINISH:
            texture.LoadFromFile("flag.png");
            sprite.SetTexture(texture);
            sprite.SetOrigin(sprite.GetLocalBounds().Width/2.0f,sprite.GetLocalBounds().Height/2.0f);
            break;
        case SWITCH:
            texture.LoadFromFile("flag.png");
            sprite.SetTexture(texture);
            sprite.SetOrigin(sprite.GetLocalBounds().Width/2.0f,sprite.GetLocalBounds().Height/2.0f);
            break;
        default:
            break;
    }

    box.SetAsBox(sprite.GetLocalBounds().Width/200.0f,sprite.GetLocalBounds().Height/200.0f);
    fixturedef.shape = &box;
    fixturedef.density = 1.0f;
    fixturedef.isSensor = true;
    fixturedef.filter.categoryBits = Element::INTERACTIVE;
    fixturedef.filter.maskBits = Element::CHARACTER;
    body->CreateFixture(&fixturedef);
    body->SetUserData(this);
}

int InteractiveDecor::GetType()
{
    return type;
}
