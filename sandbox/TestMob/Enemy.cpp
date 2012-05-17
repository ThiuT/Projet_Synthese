#include "Enemy.hpp"

Enemy::Enemy(b2World* world,float32 x,float32 y) : Mob(world,x,y,"smb3-mario_sheet.png",sf::IntRect(5,82,13,26)), iaThread(&Enemy::IA,this)
{
    ID = "ENEMY";
    body->SetUserData(this);
    sprite.SetScale(-1,1);
    iaType = 1;
}

void Enemy::StartIA()
{
    iaThread.Launch();
}

void Enemy::StopIA()
{
    iaThread.Terminate();
}

void Enemy::IA()
{
    switch(iaType) {
        case 1:
            printf("Debut de l'IA");
            break;
        default:
            break;
    }
}

Enemy::~Enemy()
{
}
