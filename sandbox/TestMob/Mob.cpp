#include "Mob.hpp"

Mob::Mob(b2World* world,float32 x,float32 y) : DynamicElement(world,x,y,true)
{
    animationTimer = 0;
    canJump = false;
    canClimb = false;
}

b2Vec2 Mob::GetPosition()
{
    return body->GetPosition();
}

void Mob::Move(int dir, float32 speed)
{
    b2Vec2 vel = body->GetLinearVelocity();
    vel.x = speed*dir;
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

void Mob::Render(sf::RenderWindow* window) {

    if(body->GetGravityScale()==0) {
    }
    else {
        b2Vec2 vel = body->GetLinearVelocity();
        if(vel.y==0) {
            if(vel.x==0) {
                sprite.SetTextureRect(sf::IntRect(5,82,13,26));
            }
            else {
                animationTimer = (animationTimer+1)%100;
                if(animationTimer<50)
                    sprite.SetTextureRect(sf::IntRect(64,84,15,24));
                else
                    sprite.SetTextureRect(sf::IntRect(34,82,15,26));
            }
        }
        else {
            sprite.SetTextureRect(sf::IntRect(94,83,15,26));
        }
    }

    sprite.SetPosition(body->GetPosition().x*100, window->GetHeight()-body->GetPosition().y*100);
    window->Draw(sprite);
}
