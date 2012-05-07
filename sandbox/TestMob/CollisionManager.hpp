#ifndef COLLISIONMANAGER_HPP_INCLUDED
#define COLLISIONMANAGER_HPP_INCLUDED

#include <Box2D/Box2D.h>
#include "Mob.hpp"

class CollisionManager : public b2ContactListener
{
    private:
        b2WorldManifold manifold;

    public:
        CollisionManager();
        void BeginContact(b2Contact* contact);
};

#endif // COLLISIONMANAGER_HPP_INCLUDED
