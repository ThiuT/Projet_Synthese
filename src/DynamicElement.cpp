/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file DynamicElement.cpp
 * @brief Implémentation des éléments dynamiques
 *
 * Ce fichier implémente les méthodes de la classe DynamicElement
 */

#include "DynamicElement.hpp"

/** @brief Constructeur par défaut
 *
 * Utile dans certains cas
 *
 */
DynamicElement::DynamicElement()
{
}

/** @brief Constructeur
 *
 * Ce constructeur est le plus fréquemment utilisé.
 *
 * @param world : pointeur vers le monde Box2D
 * @param x : position initiale x
 * @param y : position initiale y
 * @param r : autoriser ou pas la rotation (la plupart du temps on souhaite que les éléments restent debout)
 */
DynamicElement::DynamicElement(b2World* world, float32 x,float32 y,bool r)
{
    // Definition d'un corps dynamique à la position initiale x,y
    bodydef.type = b2_dynamicBody;
    bodydef.position.Set(x,y);
    bodydef.fixedRotation = r;

    // Création du corps
    body = world->CreateBody(&bodydef);

    destroyed = false;
}

/** @brief Accesseur corps
 *
 * Permet d'accéder au corps physique de l'élément
 */
b2Body* DynamicElement::GetBody()
{
    return body;
}

/** @brief Accesseur sprite
 *
 * Permet d'accéder à la composante graphique de l'élément
 */
sf::Sprite DynamicElement::GetSprite()
{
    return sprite;
}

/** @brief Affichage
 *
 * Affiche l'élément graphique à la position du corps physique
 *
 * @param : window : pointeur vers la fenêtre de rendu
 */
void DynamicElement::Render(sf::RenderWindow* window)
{
    sprite.SetPosition(body->GetPosition().x*100, window->GetHeight()-body->GetPosition().y*100);
    window->Draw(sprite);
}

/** @brief Test détruit
 *
 * Teste si l'élément doit être détruit
 *
 */
bool DynamicElement::IsDestroyed()
{
    return destroyed;
}

/** @brief Destruction
 *
 * Signale que l'élément doit être détruit
 *
 */
void DynamicElement::Destroy()
{
    destroyed = true;
}

/** @brief Destructeur
 *
 * Retire le corps du monde avant de détruire l'élément
 *
 */
DynamicElement::~DynamicElement()
{
    body->GetWorld()->DestroyBody(body);
}
