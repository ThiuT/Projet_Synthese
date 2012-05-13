#include "Mob.hpp"

Mob::Mob(b2World* world,float32 x,float32 y,string texturePath,sf::IntRect subRect) : DynamicElement(world,x,y,true)
{
    // Création du sprite
    texture.LoadFromFile(texturePath);
    sprite.SetTexture(texture);
    sprite.SetTextureRect(subRect);
    sprite.SetOrigin(sprite.GetLocalBounds().Width/2.0f,sprite.GetLocalBounds().Height/2.0f);

    // Création de la hitbox
    box.SetAsBox(sprite.GetLocalBounds().Width/200.0f,sprite.GetLocalBounds().Height/200.0f);
    fixturedef.shape = &box;
    fixturedef.density = 1.0f;
    fixturedef.friction = 1.0f;
    body->CreateFixture(&fixturedef);
}

void Mob::Move(int dir)
{
    b2Vec2 vel = body->GetLinearVelocity();
    vel.x = 0.3f*dir;
    body->SetLinearVelocity(vel);
    if(dir!=0) sprite.SetScale(-dir,1);
}

void Mob::Jump(b2Vec2 vec,bool force)
{
    if(force)
        body->ApplyLinearImpulse(vec,body->GetLocalCenter());
    else if(canJump)
        body->ApplyLinearImpulse(vec,body->GetLocalCenter());
}

void Mob::Climb(int dir)
{
    if(canClimb) {
        b2Vec2 vel = body->GetLinearVelocity();
        vel.y = 0.3f*dir;
        body->SetLinearVelocity(vel);
    }
}

void Mob::AllowJump(bool allow)
{
    canJump = allow;
}

void Mob::AllowClimb(bool allow)
{
    canClimb = allow;
}
