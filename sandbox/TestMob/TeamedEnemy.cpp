#include "TeamedEnemy.hpp"

TeamedEnemy::TeamedEnemy(b2World* world, float32 x, float32 y, string texturePath, sf::IntRect subRect) : Enemy(world,x,y,texturePath,subRect,1)
{
    ID = "ENEMY";
    body->SetUserData(this);
    iaTimer = 0;
    team = new TeamedEnemy(world,x+0.5f,y+0.5f,texturePath,subRect);
}

TeamedEnemy::~TeamedEnemy()
{
    delete team;
}
