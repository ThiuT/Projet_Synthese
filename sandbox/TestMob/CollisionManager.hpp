#ifndef COLLISIONMANAGER_HPP_INCLUDED
#define COLLISIONMANAGER_HPP_INCLUDED

#include <Box2D/Box2D.h>

class CollisionManager
{
    private:
        b2World* world;

    public:
        CollisionManager(b2World*);
        static void Run();
};

#endif // COLLISIONMANAGER_HPP_INCLUDED
