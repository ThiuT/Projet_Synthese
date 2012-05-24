#include "Character.hpp"

Character::Character(b2World* world,float32 x,float32 y) : Mob(world,x,y)
{
    // Création du sprite
    texture.LoadFromFile("character.png");
    sprite.SetTexture(texture);
    sprite.SetTextureRect(sf::IntRect(3,2,13,26));
    sprite.SetOrigin(sprite.GetLocalBounds().Width/2.0f,sprite.GetLocalBounds().Height/2.0f);

    // Création de la hitbox
    box.SetAsBox(sprite.GetLocalBounds().Width/200.0f,sprite.GetLocalBounds().Height/200.0f);
    fixturedef.shape = &box;
    fixturedef.density = 1.0f;
    fixturedef.friction = 1.0f;
    fixturedef.filter.categoryBits = Element::CHARACTER;
    fixturedef.filter.maskBits = Element::ALL;
    body->CreateFixture(&fixturedef);

    ID = "CHARACTER";
    body->SetUserData(this);
    sprite.SetScale(-1,1);

    weapon=NULL;
    victory = false;
}

void Character::Render(sf::RenderWindow* window)
{
    if(victory)
        sprite.SetTextureRect(sf::IntRect(116,4,18,27));
    else if(weapon) {
        if(weapon->IsDone()) {
            delete weapon;
            weapon=NULL;
            sprite.SetTextureRect(sf::IntRect(116,4,18,27));
        }
        else {
            sprite.SetTextureRect(sf::IntRect(116,4,18,27));
            weapon->Render(window);
        }
    }
    else {
        b2Vec2 vel = body->GetLinearVelocity();
        if(body->GetGravityScale()==0) {
            if(vel.x==0 && vel.y==0)
                sprite.SetTextureRect(sf::IntRect(168,4,16,27));
            else {
                sprite.SetTextureRect(sf::IntRect(142,4,16,25));
                animationTimer = (animationTimer+1)%100;
                if(animationTimer<50)
                    sprite.SetScale(1,1);
                else
                    sprite.SetScale(-1,1);
            }
        }
        else {
            if(vel.y==0) {
                if(vel.x==0) {
                    sprite.SetTextureRect(sf::IntRect(2,2,16,27));
                }
                else {
                    animationTimer = (animationTimer+1)%100;
                    if(animationTimer<50)
                        sprite.SetTextureRect(sf::IntRect(32,2,16,28));
                    else
                        sprite.SetTextureRect(sf::IntRect(62,3,16,28));
                }
            }
            else
                sprite.SetTextureRect(sf::IntRect(92,3,16,26));
        }
    }
    Mob::Render(window);
}

void Character::Attack(int time)
{
    if(!weapon)
        weapon = new Weapon(this);
}

void Character::Win()
{
    victory=true;
}

bool Character::HasWon()
{
    return victory;
}
