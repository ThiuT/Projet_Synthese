#include "Enemy.hpp"

Enemy::Enemy(b2World* world,float32 x,float32 y) : Mob(world,x,y,"smb3-mario_sheet.png",sf::IntRect(5,82,13,26))
{
    sprite.SetScale(-1,1);
}