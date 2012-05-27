/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file Weapon.hpp
 * @brief Déclaration des armes
 *
 * Ce fichier déclare la classe Weapon, représentant l'arme du personnage.
 */

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
