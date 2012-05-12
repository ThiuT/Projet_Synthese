#ifndef STATICELEMENT_HPP_INCLUDED
#define STATICELEMENT_HPP_INCLUDED

#include "Element.hpp"

class StaticElement : public Element
{
    public:
        StaticElement(b2World*,float32,float32);
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
