/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file CollisionManager.hpp
 * @brief Déclaration du gestionnaire de collisions
 *
 * Ce fichier déclara la classe CollisionManager dont les méthodes
 * seront appelées par callback lors des collisions
 */

#ifndef COLLISIONMANAGER_HPP_INCLUDED
#define COLLISIONMANAGER_HPP_INCLUDED

#include <Box2D/Box2D.h>
#include "Character.hpp"
#include "Enemy.hpp"
#include "Platform.hpp"
#include "InteractiveDecor.hpp"
#include <stdio.h>
#include <string>

class CollisionManager : public b2ContactListener
{
    private:
        b2WorldManifold manifold;

    public:
        CollisionManager();
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif // COLLISIONMANAGER_HPP_INCLUDED
