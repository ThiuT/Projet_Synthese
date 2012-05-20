#ifndef TEAMEDENEMY_HPP_INCLUDED
#define TEAMEDENEMY_HPP_INCLUDED

#include "Enemy.hpp"

class TeamedEnemy : public Enemy
{
    public:
        TeamedEnemy(b2World*,float32,float32,string,sf::IntRect);
        ~TeamedEnemy();

    protected:
        TeamedEnemy* team;
};

#endif // TEAMEDENEMY_HPP_INCLUDED
