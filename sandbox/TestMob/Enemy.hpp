#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#include "Mob.hpp"

class Enemy : public Mob
{
    public:
        Enemy(b2World*,float32,float32,string,sf::IntRect);
        void IA(b2Vec2 playerPosition);
        ~Enemy();

    protected:
        int iaType;
        int iaTimer;
};



#endif // ENEMY_HPP_INCLUDED
