#ifndef HANDWEAPON_HPP_INCLUDED
#define HANDWEAPON_HPP_INCLUDED

#include "Weapon.hpp"

class HandWeapon : public Weapon
{
    public:
        HandWeapon(Mob*);
        bool IsDone();
        ~HandWeapon();

    protected:
        int timer;
        b2PrismaticJoint* joint;
        b2PrismaticJointDef jointdef;
};
#endif // HANDWEAPON_HPP_INCLUDED
