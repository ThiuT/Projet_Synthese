#include "Character.hpp"

Character::Character(b2World* world,float32 x,float32 y) : Mob(world,x,y)
{
    // Création du sprite
    texture.LoadFromFile("smb3-mario_sheet.png");
    sprite.SetTexture(texture);
    sprite.SetTextureRect(sf::IntRect(5,82,13,26));
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
}

void Character::Render(sf::RenderWindow* window)
{
    Mob::Render(window);
    if(weapon) {
        if(weapon->IsDone()) {
            delete weapon;
            weapon=NULL;
        }
        else
            weapon->Render(window);
    }
}

void Character::Attack(int time)
{
    if(!weapon)
        weapon = new Weapon(this);
}
