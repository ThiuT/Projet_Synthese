/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file Mob.hpp
 * @brief Déclaration des mobs
 *
 * Ce fichier déclare la classe Mob (Mobile OBject) représentant
 * de manière générique les entités mouvantes (personnage et ennemis).
 */

#ifndef MOB_HPP_INCLUDED
#define MOB_HPP_INCLUDED

#include "DynamicElement.hpp"

using namespace std;

class Mob : public DynamicElement
{
    public:
        // Directions
        static const int LEFT = -1;
        static const int RIGHT = 1;
        static const int UP = 1;
        static const int DOWN = -1;
        static const int STOP = 0;

        Mob(b2World*,float32,float32);
        b2Vec2 GetPosition();
        void Move(int dir, float32 speed);
        void Render(sf::RenderWindow*);

        void AllowJump(bool);
        void Jump(b2Vec2 vec,bool force=false);

        void AllowClimb(bool);
        void Climb(int dir);

        float32 GetB2Height();

    protected:
        bool canJump;
        bool canClimb;
        int animationTimer;
};

#endif // MOB_HPP_INCLUDED
