#include "Enemy.hpp"

Enemy::Enemy(b2World* world,float32 x,float32 y, int ia, string texturePath, sf::IntRect subRect) : Mob(world,x,y)
{
    if(texturePath.compare("default")==0) {
        if(ia==1)
            texturePath = "green_turtle.png";
        else
            texturePath = "red_turtle.png";
    }
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
    fixturedef.filter.categoryBits = Element::ENEMY;
    fixturedef.filter.maskBits = Element::ALL;
    body->CreateFixture(&fixturedef);

    radar.m_radius = 0.5f;
    radar.m_p.x -= radar.m_radius;
    radar.m_p.y += radar.m_radius;
    radarFixture.shape = &radar;
    radarFixture.isSensor = true;
    radarFixture.filter.categoryBits = Element::RADAR;
    radarFixture.filter.maskBits = Element::CHARACTER | Element::ENEMY;
    body->CreateFixture(&radarFixture);

    ID = "ENEMY";
    body->SetUserData(this);
    sprite.SetScale(1,1);
    iaType = ia;
    iaTimer = 0;
}

void Enemy::Render(sf::RenderWindow* window)
{
    animationTimer = (animationTimer+1)%80;
    if(animationTimer<40)
        sprite.SetTextureRect(sf::IntRect(1,1,18,28));
    else
        sprite.SetTextureRect(sf::IntRect(20,1,18,28));
    Mob::Render(window);
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
                if(iaTimer<300)
                    Move(Mob::LEFT,0.2f);
                else
                    Move(Mob::RIGHT,0.2f);
                iaTimer = (iaTimer+1)%600;
                break;
            case 2:
                if(iaTimer<100)
                    Move(Mob::LEFT,0.2f);
                else
                    Move(Mob::RIGHT,0.2f);
                iaTimer = (iaTimer+1)%200;
                break;
            default:
                break;
        }
    }
}

Enemy::~Enemy()
{
}
