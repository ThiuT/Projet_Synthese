#include "CollisionManager.hpp"
#include <stdio.h>

CollisionManager::CollisionManager()
{
}

void CollisionManager::BeginContact(b2Contact* contact)
{
    Mob* mobA = static_cast<Mob*>(contact->GetFixtureA()->GetBody()->GetUserData());
    Mob* mobB = static_cast<Mob*>(contact->GetFixtureB()->GetBody()->GetUserData());

    // En cas de contact entre le personnage et un ennemi
    if(mobA && mobB && mobA->GetID()==Mob::CHARACTER && mobB->GetID()==Mob::ENEMY) {
        printf("Character contacts an enemy\n");
        contact->GetWorldManifold(&manifold);
        printf("Collision normal : (%f;%f)\n",manifold.normal.x,manifold.normal.y);
        // En cas de collision vers le bas (sur la tête du mob)
        if(manifold.normal.y<0) {
            mobA->Jump(b2Vec2(0.0f,0.07f),true);
            mobB->SetDead(true);
        }
    }
}
