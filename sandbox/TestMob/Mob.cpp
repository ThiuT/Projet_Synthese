#include "Mob.hpp"

Mob::Mob(b2World* world,float32 x,float32 y)
{
    texture.LoadFromFile("smb3-mario_sheet.png");
    sprite.SetTexture(texture);
    sprite.SetTextureRect(sf::IntRect(5,82,13,26));
    sprite.SetOrigin(sprite.GetLocalBounds().Width/2.0f,sprite.GetLocalBounds().Height/2.0f);
    sprite.Scale(-1,1);

    // Definition d'un corps dynamique à la position initiale x,y
    bodydef.type = b2_dynamicBody;
    bodydef.position.Set(x,y);
    bodydef.fixedRotation = true;

    // Création du corps
    body = world->CreateBody(&bodydef);

    // Création de la hitbox
    box.SetAsBox(sprite.GetLocalBounds().Width/200.0f,sprite.GetLocalBounds().Height/200.0f);
    fixturedef.shape = &box;
    fixturedef.density = 1.0f;
    fixturedef.friction = 2.0f;
    body->CreateFixture(&fixturedef);
}

void Mob::Render(sf::RenderWindow* window)
{
    sprite.SetPosition(body->GetPosition().x*100, window->GetHeight()-body->GetPosition().y*100);
    window->Draw(sprite);
}

void Mob::Move(int dir)
{
    body->SetLinearVelocity(b2Vec2(0.3f*dir,0.0f));
}
