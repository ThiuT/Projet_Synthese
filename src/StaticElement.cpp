/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file StaticElement.cpp
 * @brief Implémentation des éléments statiques
 *
 * Ce fichier implémente les méthodes de la classe StaticElement
 */

#include "StaticElement.hpp"

/** @brief Constructeur
 *
 * Crée un corps statique à la position demandée.
 *
 * @param world : pointeur vers le monde Box2D
 * @param x : position initiale x
 * @param y : position initiale y
 */
StaticElement::StaticElement(b2World* world, float32 x, float32 y)
{
    bodydef.type = b2_staticBody;
    bodydef.position.Set(x,y);
    body = world->CreateBody(&bodydef);
}

/** @brief Accesseur corps
 *
 * Permet d'accéder au corps physique de l'élément
 */
b2Body* StaticElement::GetBody()
{
    return body;
}

/** @brief Affichage
 *
 * Affiche l'élément graphique à la position du corps physique
 *
 * @param : window : pointeur vers la fenêtre de rendu
 */
void StaticElement::Render(sf::RenderWindow* window)
{
    sprite.SetPosition(body->GetPosition().x*100, window->GetHeight()-body->GetPosition().y*100);
    window->Draw(sprite);
}

/** @brief Destructeur
 *
 * Retire le corps du monde avant de détruire l'élément
 *
 */
StaticElement::~StaticElement()
{
    body->GetWorld()->DestroyBody(body);
}
