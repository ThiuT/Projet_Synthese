/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file Mob.cpp
 * @brief Implémentation des mobs
 *
 * Ce fichier implémente les méthodes de la classe Mob
 */

#include "Mob.hpp"

/** @brief Constructeur
 *
 * Appelle le constructeur de DynamicElement à la position voulue,
 * vérouillé en rotation (les mobs restent debout), puis initialise
 * des attributs propres à la classe.
 *
 * @param world : pointeur vers le monde Box2D
 * @param x : position initiale x
 * @param y : position initiale y
 */
Mob::Mob(b2World* world,float32 x,float32 y) : DynamicElement(world,x,y,true)
{
    animationTimer = 0;
    canJump = false;
    canClimb = false;
}

/** @brief Accesseur de position
 *
 * Méthode utilitaire permettant d'accéder à la position
 * du corps physique du mob
 *
 */
b2Vec2 Mob::GetPosition()
{
    return body->GetPosition();
}


/** @brief Déplacement
 *
 * Méthode de déplacement par modification du vecteur de vélocité.
 *
 * @param dir : +1 pour droite, -1 pour gauche (constantes de classe)
 * @param speed : la vitesse du déplacement
 */
void Mob::Move(int dir, float32 speed)
{
    b2Vec2 vel = body->GetLinearVelocity();
    vel.x = speed*dir;
    body->SetLinearVelocity(vel);
    if(dir!=0) sprite.SetScale(-dir,1);
}

/** @brief Saut
 *
 * Méthode de saut par impulsion
 *
 * @param vec : le vecteur de l'impulsion
 * @param force : permet de forcer le saut en cas de besoin
 */
void Mob::Jump(b2Vec2 vec,bool force)
{
    body->SetLinearDamping(0.0f);
    body->SetGravityScale(1.0f);
    if(force)
        body->ApplyLinearImpulse(vec,body->GetLocalCenter());
    else if(canJump)
        body->ApplyLinearImpulse(vec,body->GetLocalCenter());
        AllowJump(false);
}

/** @brief Grimper
 *
 * Méthode permettant de grimper à une échelle.
 *
 * @param dir : +1 pour haut, -1 pour bas (constantes de classe)
 *
 */
void Mob::Climb(int dir)
{
    if(canClimb) {
        body->SetGravityScale(0);
        body->SetLinearDamping(10.0f);
        AllowJump(true);
        b2Vec2 vel = body->GetLinearVelocity();
        vel.y = 0.3f*dir;
        body->SetLinearVelocity(vel);
    }
    else
        body->SetGravityScale(1);
}

/** @brief Autorisation de saut
 *
 * Méthode appelée par le gestionnaire de collisions
 * pour signaler la possibilté ou non de sauter.
 *
 * @param allow : booleen d'autorisation
 */
void Mob::AllowJump(bool allow)
{
    canJump = allow;
}

/** @brief Autorisation de grimper
 *
 * Méthode appelée par le gestionnaire de collisions
 * pour signaler la possibilté ou non de grimper.
 *
 * @param allow : booleen d'autorisation
 */
void Mob::AllowClimb(bool allow)
{
    canClimb = allow;
}

/** @brief Accesseur hauteur
 *
 * Méthode appelée par le gestionnaire de collisions
 * pour connaître la taille verticale du mob (utile pour
 * la gestion des clouds).
 */
float32 Mob::GetB2Height()
{
    return sprite.GetLocalBounds().Height/200.0f;
}

/** @brief Fonction d'affichage
 *
 * Méthode d'affichage de base qui récupère la position du corps physique
 * et dessine le corps graphique à cette position.
 *
 * @param window : pointeur vers la fenêtre de rendu
 */
void Mob::Render(sf::RenderWindow* window)
{
    sprite.SetPosition(body->GetPosition().x*100, window->GetHeight()-body->GetPosition().y*100);
    window->Draw(sprite);
}
