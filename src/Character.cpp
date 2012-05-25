/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file Character.cpp
 * @brief Implémentation du personnage
 *
 * Ce fichier implémente les méthodes de la classe Character
 */

#include "Character.hpp"

/** @brief Constructeur
 *
 * Le constructeur, appelle le constructeur de Mob avec les
 * mêmes paramètres puis ajoute la composante graphique,
 * et le filtrage
 *
 * @param world : pointeur vers le monde Box2D
 * @param x : position initiale x
 * @param y : position initiale y
 */
Character::Character(b2World* world,float32 x,float32 y) : Mob(world,x,y)
{
    // Création du sprite
    texture.LoadFromFile("src/ressources/character.png");
    sprite.SetTexture(texture);
    sprite.SetTextureRect(sf::IntRect(3,2,13,26));
    sprite.SetOrigin(sprite.GetLocalBounds().Width/2.0f,sprite.GetLocalBounds().Height/2.0f);

    // Création de la hitbox
    box.SetAsBox(sprite.GetLocalBounds().Width/200.0f,sprite.GetLocalBounds().Height/200.0f);
    fixturedef.shape = &box;
    fixturedef.density = 1.0f;
    fixturedef.friction = 1.0f;
    fixturedef.filter.categoryBits = Element::CHARACTER;
    fixturedef.filter.maskBits = Element::ALL;
    body->CreateFixture(&fixturedef);

    body->SetUserData(this);
    // Le sprite est retourné pour regarder initialement à droite
    sprite.SetScale(-1,1);

    weapon=NULL;
    victory = false;
}

/** @brief Fonction d'affichage
 *
 * En fonction de l'état et du mouvement, choisit la partie
 * de la feuille de sprite à afficher, puis appelle l'affichage
 * générique de la classe Mob.
 *
 * @param window : pointeur vers la fenêtre de rendu
 */
void Character::Render(sf::RenderWindow* window)
{
    // En cas de victoire
    if(victory)
        sprite.SetTextureRect(sf::IntRect(116,4,18,27));

    // Si une attaque est en cours
    else if(weapon) {
        // Si l'attaque est terminée
        if(weapon->IsDone()) {
            delete weapon;
            weapon=NULL;
            sprite.SetTextureRect(sf::IntRect(116,4,18,27));
        }
        // Sinon on affiche l'arme
        else {
            sprite.SetTextureRect(sf::IntRect(116,4,18,27));
            weapon->Render(window);
        }
    }

    else {
        b2Vec2 vel = body->GetLinearVelocity();
        // Si pas de gravité (=échelle)
        if(body->GetGravityScale()==0) {
            if(vel.x==0 && vel.y==0)
                sprite.SetTextureRect(sf::IntRect(168,4,16,27));
            else {
                sprite.SetTextureRect(sf::IntRect(142,4,16,25));
                animationTimer = (animationTimer+1)%100;
                if(animationTimer<50)
                    sprite.SetScale(1,1);
                else
                    sprite.SetScale(-1,1);
            }
        }
        else {
            if(vel.y==0) {
                // Si immobile
                if(vel.x==0) {
                    sprite.SetTextureRect(sf::IntRect(2,2,16,27));
                }
                // Si déplacement latéral
                else {
                    animationTimer = (animationTimer+1)%100;
                    if(animationTimer<50)
                        sprite.SetTextureRect(sf::IntRect(32,2,16,28));
                    else
                        sprite.SetTextureRect(sf::IntRect(62,3,16,28));
                }
            }
            // Si en l'air
            else
                sprite.SetTextureRect(sf::IntRect(92,3,16,26));
        }
    }
    // Appel de la méthode générique
    Mob::Render(window);
}

/** @brief Attaque
 *
 * Le personnage attaque : une arme apparait devant lui
 * pour un temps fixe. Le contact de l'arme est mortel
 * pour les ennemis.
 *
 */
void Character::Attack()
{
    if(!weapon)
        weapon = new Weapon(this);
}

/** @brief Victoire
 *
 * Permet de signaler la fin du niveau
 *
 */
void Character::Win()
{
    victory=true;
}

/** @brief Test victoire
 *
 * Permet de tester si la fin de niveau est atteinte
 *
 */
bool Character::HasWon()
{
    return victory;
}
