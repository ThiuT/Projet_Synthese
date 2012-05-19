#include "FlyingEnemy.hpp"

FlyingEnemy::FlyingEnemy(b2World* world,float32 x,float32 y, string texturePath, sf::IntRect subRect) : Enemy(world,x,y,texturePath,subRect)
{
    ID = "ENEMY";
    body->SetUserData(this);
    //sprite.SetScale(-1,1);
    body->SetGravityScale(0.0f);
    body->SetLinearDamping(10.0f);
    iaType = 1;
    iaTimer = 0;
}

FlyingEnemy::~FlyingEnemy()
{
}
