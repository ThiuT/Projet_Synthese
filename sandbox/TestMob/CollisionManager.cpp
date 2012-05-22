#include "CollisionManager.hpp"

CollisionManager::CollisionManager()
{
}

// Callback au début d'un contact
void CollisionManager::BeginContact(b2Contact* contact)
{
    uint16 categoryA = contact->GetFixtureA()->GetFilterData().categoryBits;
    uint16 categoryB = contact->GetFixtureB()->GetFilterData().categoryBits;
    contact->GetWorldManifold(&manifold);

    // En cas de contact entre le personnage et un ennemi
    if(categoryA==Element::CHARACTER && categoryB==Element::ENEMY) {
        Character* character = static_cast<Character*>(contact->GetFixtureA()->GetBody()->GetUserData());
        Enemy* enemy = static_cast<Enemy*>(contact->GetFixtureB()->GetBody()->GetUserData());
        // En cas de collision vers le bas (sur la tête du mob), il est détruit
        if(manifold.normal.y<0) {
            character->Jump(b2Vec2(0.0f,0.07f),true);
            enemy->Destroy();
        }
        // Sinon le personnage meurt
        else character->Destroy();
    }

    else if(categoryA==Element::PLATFORM && categoryB==Element::CHARACTER) {
        Character* character = static_cast<Character*>(contact->GetFixtureB()->GetBody()->GetUserData());
        // En cas de collision sur le sommet d'une plate forme
        if(manifold.normal.y>0)
            character->AllowJump(true);
    }

    else if(categoryA==Element::INTERACTIVE && categoryB==Element::CHARACTER) {
        Character* character = static_cast<Character*>(contact->GetFixtureB()->GetBody()->GetUserData());
        character->AllowClimb(true);
    }

    else if(categoryB==Element::WEAPON) {
        Mob* mob = static_cast<Mob*>(contact->GetFixtureA()->GetBody()->GetUserData());
        mob->Destroy();
    }
}

// Callback lorsqu'un contact se termine
void CollisionManager::EndContact(b2Contact* contact)
{
    uint16 categoryA = contact->GetFixtureA()->GetFilterData().categoryBits;
    uint16 categoryB = contact->GetFixtureB()->GetFilterData().categoryBits;
    contact->GetWorldManifold(&manifold);

    // En cas de fin de contact avec une plate-forme
    if(categoryA==Element::PLATFORM && categoryB==Element::CHARACTER) {
        Character* character = static_cast<Character*>(contact->GetFixtureB()->GetBody()->GetUserData());
        character->AllowJump(false);
    }
    else if(categoryA==Element::INTERACTIVE && categoryB==Element::CHARACTER) {
        Character* character = static_cast<Character*>(contact->GetFixtureB()->GetBody()->GetUserData());
        character->AllowClimb(false);
        contact->GetFixtureB()->GetBody()->SetGravityScale(1);
        contact->GetFixtureB()->GetBody()->SetLinearDamping(0.0f);
    }
}


// Callback avant résolution d'un contact
void CollisionManager::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    uint16 categoryA = contact->GetFixtureA()->GetFilterData().categoryBits;
    uint16 categoryB = contact->GetFixtureB()->GetFilterData().categoryBits;
    contact->GetWorldManifold(&manifold);

    // En cas de collision entre le personnage et une plate-forme
    if(categoryA==Element::PLATFORM && categoryB==Element::CHARACTER) {
        Platform* platform = static_cast<Platform*>(contact->GetFixtureA()->GetBody()->GetUserData());
        Character* character = static_cast<Character*>(contact->GetFixtureB()->GetBody()->GetUserData());

        // En cas de collision sur le sommet d'une plate forme
        if(manifold.normal.y>0)
            character->AllowJump(true);

        // Si le personnage entre en contact avec le côté de la plate forme, la friction devient nulle
        // Le personnage glisse le long des côtés des plates-formes
        if(manifold.normal.y==0.0f)
            contact->SetFriction(0.0f);
        else
            contact->SetFriction(1.0f);

        // Si le personnage est en dessous de la plate-forme et qu'il s'agit d'un cloud, on ignore la collision
        if(platform->IsCloud()) {
            float32 mob_y = contact->GetFixtureB()->GetBody()->GetPosition().y;
            float32 mob_size = character->GetB2Height();
            float32 platform_y = contact->GetFixtureA()->GetBody()->GetPosition().y;
            if(mob_y-platform_y < mob_size) contact->SetEnabled(false);
        }
    }
}

void CollisionManager::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}
