#ifndef FLYINGENEMY_HPP_INCLUDED
#define FLYINGENEMY_HPP_INCLUDED

#include "Enemy.hpp"

class FlyingEnemy : public Enemy
{
    public:
        FlyingEnemy(b2World*,float32,float32);
        ~FlyingEnemy();
};

#endif // FLYINGENEMY_HPP_INCLUDED
