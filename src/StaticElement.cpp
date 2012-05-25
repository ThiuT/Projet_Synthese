#include "StaticElement.hpp"

StaticElement::StaticElement(b2World* world, float32 x, float32 y)
{
    bodydef.type = b2_staticBody;
    bodydef.position.Set(x,y);
    body = world->CreateBody(&bodydef);
}

b2Body* StaticElement::GetBody()
{
    return body;
}

void StaticElement::Render(sf::RenderWindow* window)
{
    sprite.SetPosition(body->GetPosition().x*100, window->GetHeight()-body->GetPosition().y*100);
    window->Draw(sprite);
}

StaticElement::~StaticElement()
{
    body->GetWorld()->DestroyBody(body);
}
