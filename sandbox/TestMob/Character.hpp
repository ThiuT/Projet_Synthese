#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED

#include "Mob.hpp"
#include "Weapon.hpp"

class Character : public Mob
{
    public:
        Character(b2World*,float32,float32);
        void Render(sf::RenderWindow*);
        void Attack(int time);
        void Win();
        bool HasWon();

    protected:
        Weapon* weapon;
        bool victory;
};

#endif // CHARACTER_HPP_INCLUDED
