#include "CollisionManager.hpp"

CollisionManager::CollisionManager()
{
}

// Callback au début d'un contact
void CollisionManager::BeginContact(b2Contact* contact)
{
    Element* elemA = static_cast<Element*>(contact->GetFixtureA()->GetBody()->GetUserData());
    Element* elemB = static_cast<Element*>(contact->GetFixtureB()->GetBody()->GetUserData());
    std::string idA = elemA->GetID();
    std::string idB = elemB->GetID();
    contact->GetWorldManifold(&manifold);

    // En cas de contact entre le personnage et un ennemi
    if(idA.compare("CHARACTER")==0 && idB.compare("ENEMY")==0) {
        Mob* mobA = static_cast<Mob*>(elemA);
        Mob* mobB = static_cast<Mob*>(elemB);
        // En cas de collision vers le bas (sur la tête du mob), il est détruit
        if(manifold.normal.y<0) {
            mobA->Jump(b2Vec2(0.0f,0.07f),true);
            mobB->Destroy();
        }
        // Sinon le personnage meurt
        else mobA->Destroy();
    }

    else if(idA.compare("PLATFORM")==0 && idB.compare("CHARACTER")==0) {
        Mob* mobB = static_cast<Mob*>(elemB);
        // En cas de collision sur le sommet d'une plate forme
        if(manifold.normal.y>0)
            mobB->AllowJump(true);
    }
}

// Callback lorsqu'un contact se termine
void CollisionManager::EndContact(b2Contact* contact)
{
    Element* elemA = static_cast<Element*>(contact->GetFixtureA()->GetBody()->GetUserData());
    Element* elemB = static_cast<Element*>(contact->GetFixtureB()->GetBody()->GetUserData());
    std::string idA = elemA->GetID();
    std::string idB = elemB->GetID();
    contact->GetWorldManifold(&manifold);

    // En cas de fin de contact avec une plate-forme
    if(idA.compare("PLATFORM")==0 && idB.compare("CHARACTER")==0) {
        Mob* mobB = static_cast<Mob*>(elemB);
        mobB->AllowJump(false);
    }
}


// Callback avant résolution d'un contact
void CollisionManager::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    Element* elemA = static_cast<Element*>(contact->GetFixtureA()->GetBody()->GetUserData());
    Element* elemB = static_cast<Element*>(contact->GetFixtureB()->GetBody()->GetUserData());
    std::string idA = elemA->GetID();
    std::string idB = elemB->GetID();

    // En cas de collision entre le personnage et une plate-forme
    if(elemA && elemB && idA.compare("PLATFORM")==0 && idB.compare("CHARACTER")==0) {
        contact->GetWorldManifold(&manifold);
        // Si le personnage entre en contact avec le côté de la plate forme, la friction devient nulle
        // Le personnage glisse le long des côtés des plates-formes
        if(manifold.normal.y==0.0f)
            contact->SetFriction(0.0f);
    }
}
