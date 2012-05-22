#ifndef WEAPON_HPP_INCLUDED
#define WEAPON_HPP_INCLUDED

#include "DynamicElement.hpp"
#include "Mob.hpp"

class Weapon : public DynamicElement
{
    public:
        Weapon(Mob*);
        bool IsDone();
        ~Weapon();

    protected:
        Mob* user;
        int timer;
        b2PrismaticJoint* joint;
        b2PrismaticJointDef jointdef;
};

#endif // WEAPON_HPP_INCLUDED
