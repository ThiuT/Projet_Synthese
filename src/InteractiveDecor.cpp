/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file InteractiveDecor.cpp
 * @brief Implémentation des décors interactifs
 *
 * Ce fichier implémente les méthodes de la classe InteractiveDecor
 */

#include "InteractiveDecor.hpp"

/** @brief Constructeur
 *
 * Appelle le constructeur de StaticElement à la position donnée,
 * rajoute les composantes graphiques en fonction du type
 *
 * @param world : pointeur vers le monde Box2D
 * @param x : position initiale x
 * @param y : position initiale y
 * @param width :  largeur de l'élément
 * @param height : hauteur de l'élément
 * @param t : type d'élément
 */
InteractiveDecor::InteractiveDecor(b2World* world, float32 x, float32 y, float32 width, float32 height, int t) : StaticElement(world,x,y)
{
    type = t;
    switch(type) {
        case LADDER:
            texture.LoadFromFile("src/ressources/Ladder.png");
            texture.SetRepeated(true);
            sprite.SetTexture(texture);
            sprite.SetTextureRect(sf::IntRect(0,0,texture.GetWidth(),height*200));
            sprite.SetOrigin(sprite.GetLocalBounds().Width/2.0f,sprite.GetLocalBounds().Height/2.0f);
            break;
        case FINISH:
            texture.LoadFromFile("src/ressources/flag.png");
            sprite.SetTexture(texture);
            sprite.SetOrigin(sprite.GetLocalBounds().Width/2.0f,sprite.GetLocalBounds().Height/2.0f);
            break;
        case SWITCH:
            texture.LoadFromFile("src/ressources/flag.png");
            sprite.SetTexture(texture);
            sprite.SetOrigin(sprite.GetLocalBounds().Width/2.0f,sprite.GetLocalBounds().Height/2.0f);
            break;
        default:
            break;
    }

    box.SetAsBox(sprite.GetLocalBounds().Width/200.0f,sprite.GetLocalBounds().Height/200.0f);
    fixturedef.shape = &box;
    fixturedef.density = 1.0f;
    fixturedef.isSensor = true;
    fixturedef.filter.categoryBits = Element::INTERACTIVE;
    fixturedef.filter.maskBits = Element::CHARACTER;
    body->CreateFixture(&fixturedef);
    body->SetUserData(this);
}

/** @brief Accesseur type
 *
 * Renvoie le type de l'élément
 *
 */
int InteractiveDecor::GetType()
{
    return type;
}
