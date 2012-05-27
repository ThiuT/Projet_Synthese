/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file StaticElement.hpp
 * @brief Déclaration des éléments statiques
 *
 * Ce fichier déclare la classe StaticElement, mère de
 * tous les éléments immobiles du jeu.
 */

#ifndef STATICELEMENT_HPP_INCLUDED
#define STATICELEMENT_HPP_INCLUDED

#include "Element.hpp"

class StaticElement : public Element
{
    public:
        StaticElement(b2World*,float32,float32);
        b2Body* GetBody();
        void Render(sf::RenderWindow*);
        ~StaticElement();

    protected:
        b2World* world;

        b2BodyDef bodydef;
        b2Body* body;
        b2PolygonShape box;
        b2FixtureDef fixturedef;

        sf::Texture texture;
        sf::Sprite sprite;
};

#endif // STATICELEMENT_HPP_INCLUDED