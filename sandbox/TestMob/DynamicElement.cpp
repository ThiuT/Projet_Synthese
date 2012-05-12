#include "DynamicElement.hpp"

DynamicElement::DynamicElement(b2World* world, float32 x,float32 y,bool r)
{
    // Definition d'un corps dynamique à la position initiale x,y
    bodydef.type = b2_dynamicBody;
    bodydef.position.Set(x,y);
    bodydef.fixedRotation = r;

    // Création du corps
    body = world->CreateBody(&bodydef);

    destroyed = false;
}

void DynamicElement::Render(sf::RenderWindow* window)
{
    sprite.SetPosition(body->GetPosition().x*100, window->GetHeight()-body->GetPosition().y*100);
    window->Draw(sprite);
}

bool DynamicElement::IsDestroyed()
{
    return destroyed;
}

void DynamicElement::Destroy()
{
    destroyed = true;
}

DynamicElement::~DynamicElement()
{
    body->GetWorld()->DestroyBody(body);
}
