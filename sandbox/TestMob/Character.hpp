#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED

#include "Mob.hpp"

class Character : public Mob
{
    public:
        Character(b2World*,float32,float32);
};

#endif // CHARACTER_HPP_INCLUDED
