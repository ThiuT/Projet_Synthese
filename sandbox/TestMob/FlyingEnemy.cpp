#include "FlyingEnemy.hpp"

FlyingEnemy::FlyingEnemy(b2World* world,float32 x,float32 y) : Enemy(world,x,y,1,"flying_turtle.png",sf::IntRect(2,1,16,27))
{
    ID = "ENEMY";
    body->SetUserData(this);
    //sprite.SetScale(-1,1);
    body->SetGravityScale(0.0f);
    body->SetLinearDamping(10.0f);
    iaTimer = 0;
}

FlyingEnemy::~FlyingEnemy()
{
}
