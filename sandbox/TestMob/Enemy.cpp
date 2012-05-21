#include "Enemy.hpp"

Enemy::Enemy(b2World* world,float32 x,float32 y, string texturePath, sf::IntRect subRect) : Mob(world,x,y)
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
    fixturedef.filter.categoryBits = Element::ENEMY;
    fixturedef.filter.maskBits = Element::ALL;
    body->CreateFixture(&fixturedef);

    radar.m_radius = 8.0f;
    radarFixture.shape = &radar;
    radarFixture.isSensor = true;
    radarFixture.filter.categoryBits = Element::RADAR;
    radarFixture.filter.maskBits = Element::CHARACTER | Element::ENEMY;
    body->CreateFixture(&radarFixture);

    ID = "ENEMY";
    body->SetUserData(this);
    sprite.SetScale(-1,1);
    iaType = 1;
    iaTimer = 0;
}

void Enemy::Sense(Mob* mob)
{
    mobsInRange.push_back(mob);
}

void Enemy::UnSense(Mob* mob)
{
    mobsInRange.erase(std::find(mobsInRange.begin(),mobsInRange.end(),mob));
}


void Enemy::IA(b2Vec2 playerPosition)
{
    // L'IA ne s'active qu'à moins de 6m du personnage (3/4 d'écran)
    float32 distance = fabs(playerPosition.Length() - body->GetPosition().Length());
    if(distance<6.0f) {
        switch(iaType) {
            case 1:
                if(iaTimer<400)
                    Move(Mob::LEFT,0.2f);
                else
                    Move(Mob::RIGHT,0.2f);
                iaTimer = (iaTimer+1)%800;
                break;
            default:
                break;
        }
    }
}

Enemy::~Enemy()
{
}
