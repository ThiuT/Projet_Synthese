#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#include "Mob.hpp"

class Enemy : public Mob
{
    public:
        Enemy(b2World*,float32,float32);
        void IA();
        void StartIA();
        void StopIA();
        ~Enemy();

    protected:
        int iaType;
        sf::Thread iaThread;
};



#endif // ENEMY_HPP_INCLUDED
