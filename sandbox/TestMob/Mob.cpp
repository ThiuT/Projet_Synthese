#include "Mob.hpp"

Mob::Mob(b2World* world,float32 x,float32 y)
{
    texture.LoadFromFile("MarioSprite1.png");
    sprite.SetTexture(texture);
    sprite.SetOrigin(sprite.GetLocalBounds().Width/2.0f,sprite.GetLocalBounds().Height/2.0f);

    // Definition d'un corps dynamique à la position initiale x,y
    bodydef.type = b2_dynamicBody;
    bodydef.position.Set(x,y);

    // Création du corps
    body = world->CreateBody(&bodydef);

    // Création de la hitbox
    box.SetAsBox(sprite.GetLocalBounds().Width/200.0f,sprite.GetLocalBounds().Height/200.0f);
    fixturedef.shape = &box;
    fixturedef.density = 1.0f;
    body->CreateFixture(&fixturedef);
}

void Mob::Render(sf::RenderWindow* window)
{
    sprite.SetPosition(body->GetPosition().x*100, window->GetHeight()-body->GetPosition().y*100);
    window->Draw(sprite);
}
