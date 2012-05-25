/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file FlyingEnemy.cpp
 * @brief Implémentation des ennemis volants
 *
 * Ce fichier implémente les méthodes de la classe FlyingEnemy
 */

#include "FlyingEnemy.hpp"

/** @brief Constructeur
 *
 * Appelle le constructeur de Enemy à la position donnée, avec une ia donnée
 * et une composante graphique donnée, puis supprime la gravité.
 *
 * @param world : pointeur vers le monde Box2D
 * @param x : position initiale x
 * @param y : position initiale y
 */
FlyingEnemy::FlyingEnemy(b2World* world,float32 x,float32 y) : Enemy(world,x,y,1,"src/ressources/flying_turtle.png",sf::IntRect(2,1,16,27))
{
    body->SetUserData(this);
    //sprite.SetScale(-1,1);
    body->SetGravityScale(0.0f);
    body->SetLinearDamping(10.0f);
    iaTimer = 0;
}

FlyingEnemy::~FlyingEnemy()
{
}
