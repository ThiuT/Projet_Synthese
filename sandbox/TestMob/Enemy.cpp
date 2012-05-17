#include "Enemy.hpp"

Enemy::Enemy(b2World* world,float32 x,float32 y) : Mob(world,x,y,"smb3-mario_sheet.png",sf::IntRect(5,82,13,26))
{
    ID = "ENEMY";
    body->SetUserData(this);
    sprite.SetScale(-1,1);
    iaType = 1;
    iaTimer = 0;
}


void Enemy::IA()
{
    switch(iaType) {
        case 1:
            if(iaTimer<400)
                Move(Mob::LEFT);
            else
                Move(Mob::RIGHT);
            iaTimer = (iaTimer+1)%800;
            break;
        default:
            break;
    }
}

Enemy::~Enemy()
{
}
