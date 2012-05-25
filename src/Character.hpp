/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file Character.hpp
 * @brief Déclaration du personnage
 *
 * Ce fichier déclare la classe Character représentant
 * le personnage.
 */

#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED

#include "Mob.hpp"
#include "Weapon.hpp"

class Character : public Mob
{
    public:
        Character(b2World*,float32,float32);
        void Render(sf::RenderWindow*);
        void Attack();
        void Win();
        bool HasWon();

    protected:
        Weapon* weapon;
        bool victory;
};

#endif // CHARACTER_HPP_INCLUDED
