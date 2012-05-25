/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file FlyingEnemy.hpp
 * @brief Déclaration des ennemis volants
 *
 * Ce fichier déclare la classe FlyingEnemy représentant les ennemis volants
 */

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
