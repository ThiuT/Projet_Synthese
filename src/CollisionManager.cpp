/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file CollisionManager.cpp
 * @brief Implémentation du gestionnaire de collisions
 *
 * Ce fichier implémente les méthodes appelées lors des
 * callbacks de collision.
 */

#include "CollisionManager.hpp"


/** @brief Constructeur par défaut
 *
 */
CollisionManager::CollisionManager()
{
}

/** @brief Debut de contact
 *
 * Cette méthode est appelée lorsqu'un contact commence
 *
 * @param contact : objet contenant les informations sur le contact
 */
void CollisionManager::BeginContact(b2Contact* contact)
{
    // Récupération des catégories des objets impliqués
    uint16 categoryA = contact->GetFixtureA()->GetFilterData().categoryBits;
    uint16 categoryB = contact->GetFixtureB()->GetFilterData().categoryBits;
    contact->GetWorldManifold(&manifold);

    // En cas de contact entre le personnage et un ennemi
    if(categoryA==Element::ENEMY && categoryB==Element::CHARACTER) {
        Character* character = static_cast<Character*>(contact->GetFixtureB()->GetBody()->GetUserData());
        Enemy* enemy = static_cast<Enemy*>(contact->GetFixtureA()->GetBody()->GetUserData());
        // En cas de collision vers le bas (sur la tête du mob), il est détruit
        if(manifold.normal.y>0) {
            character->Jump(b2Vec2(0.0f,0.07f),true);
            enemy->Destroy();
        }
        // Sinon le personnage meurt
        else character->Destroy();
    }

    // En cas de collision entre le personnage et une plate-forme
    else if(categoryA==Element::PLATFORM && categoryB==Element::CHARACTER) {
        Character* character = static_cast<Character*>(contact->GetFixtureB()->GetBody()->GetUserData());

        // En cas de collision sur le sommet d'une plate forme
        if(manifold.normal.y>0)
            character->AllowJump(true);
    }

    // En cas de collision entre le personnage et un élément interactif
    else if(categoryA==Element::INTERACTIVE && categoryB==Element::CHARACTER) {
        InteractiveDecor* decor = static_cast<InteractiveDecor*>(contact->GetFixtureA()->GetBody()->GetUserData());
        Character* character = static_cast<Character*>(contact->GetFixtureB()->GetBody()->GetUserData());

        // Si le décor est une échelle, on autorise le personnage à grimper
        if(decor->GetType()==InteractiveDecor::LADDER)
            character->AllowClimb(true);

        // Si le décor est l'arrivée, on signale au personnage sa victoire
        else if(decor->GetType()==InteractiveDecor::FINISH)
            character->Win();
    }

    // Si un élément entre en contact avec une arme il est détruit
    else if(categoryA==Element::WEAPON) {
        Mob* mob = static_cast<Mob*>(contact->GetFixtureB()->GetBody()->GetUserData());
        mob->Destroy();
    }

    // Surcharge car on ne maîtrise pas le sens du contact
    else if(categoryB==Element::WEAPON) {
        Mob* mob = static_cast<Mob*>(contact->GetFixtureA()->GetBody()->GetUserData());
        mob->Destroy();
    }
}

/** @brief Fin de contact
 *
 * Callback appelé lorsqu'un contact se termine
 *
 * @param contact : objet contenant les informations sur le contact
 */
void CollisionManager::EndContact(b2Contact* contact)
{
    // Récupération des catégories des objets impliqués
    uint16 categoryA = contact->GetFixtureA()->GetFilterData().categoryBits;
    uint16 categoryB = contact->GetFixtureB()->GetFilterData().categoryBits;
    contact->GetWorldManifold(&manifold);

    // En cas de fin de contact avec une plate-forme, le personnage ne peut plus sauter
    if(categoryA==Element::PLATFORM && categoryB==Element::CHARACTER) {
        Character* character = static_cast<Character*>(contact->GetFixtureB()->GetBody()->GetUserData());
        character->AllowJump(false);
    }

    // En cas de fin de contact avec un décor interactif
    else if(categoryA==Element::INTERACTIVE && categoryB==Element::CHARACTER) {
        InteractiveDecor* decor = static_cast<InteractiveDecor*>(contact->GetFixtureA()->GetBody()->GetUserData());
        Character* character = static_cast<Character*>(contact->GetFixtureB()->GetBody()->GetUserData());

        // Si c'est une échelle, le personnage ne peut plus grimper
        if(decor->GetType()==InteractiveDecor::LADDER) {
            character->AllowClimb(false);
            // On s'assure que la gravité revient à la normale
            contact->GetFixtureB()->GetBody()->SetGravityScale(1);
            contact->GetFixtureB()->GetBody()->SetLinearDamping(0.0f);
        }
    }
}


/** @brief Pré-résolution
 *
 * Callback pour un contact existant avant itération du moteur physique
 *
 * @param contact : objet contenant les informations sur le contact
 * @param oldManifold : l'état du contact à l'itération précédente
 */
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

/** @brief Post-résolution
 *
 * Callback pour un contact existant après itération du moteur physique
 *
 * @param contact : objet contenant les informations sur le contact
 * @param impulse : les forces subies par les objets en contact au cours de l'itération
 */
void CollisionManager::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}
