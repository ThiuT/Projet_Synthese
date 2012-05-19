#include "Enemy.hpp"

Enemy::Enemy(b2World* world,float32 x,float32 y, string texturePath, sf::IntRect subRect) : Mob(world,x,y,texturePath,subRect)
{
    ID = "ENEMY";
    body->SetUserData(this);
    sprite.SetScale(-1,1);
    iaType = 1;
    iaTimer = 0;
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
