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
    body->SetLinearDamping(0.0f);
    body->SetGravityScale(1.0f);
    //AllowClimb(false);
    if(force)
        body->ApplyLinearImpulse(vec,body->GetLocalCenter());
    else if(canJump)
        body->ApplyLinearImpulse(vec,body->GetLocalCenter());
        AllowJump(false);
}

void Mob::Climb(int dir)
{
    if(canClimb) {
        body->SetGravityScale(0);
        body->SetLinearDamping(10.0f);
        AllowJump(true);
        b2Vec2 vel = body->GetLinearVelocity();
        vel.y = 0.3f*dir;
        body->SetLinearVelocity(vel);
    }
    else
        body->SetGravityScale(1);
}

void Mob::AllowJump(bool allow)
{
    canJump = allow;
}

void Mob::AllowClimb(bool allow)
{
    canClimb = allow;
}

float32 Mob::GetB2Height()
{
    return sprite.GetLocalBounds().Height/200.0f;
}
