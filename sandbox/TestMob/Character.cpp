#include "Character.hpp"

Character::Character(b2World* world,float32 x,float32 y) : Mob(world,x,y,"smb3-mario_sheet.png",sf::IntRect(5,82,13,26))
{
    ID = "CHARACTER";
    body->SetUserData(this);
    sprite.SetScale(-1,1);
}
