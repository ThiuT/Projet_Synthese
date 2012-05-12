#ifndef DYNAMICELEMENT_HPP_INCLUDED
#define DYNAMICELEMENT_HPP_INCLUDED

#include "Element.hpp"

class DynamicElement : public Element
{
    public:
        DynamicElement(b2World*,float32,float32,bool);
        void Render(sf::RenderWindow*);
        bool IsDestroyed();
        void Destroy();
        ~DynamicElement();

    protected:
        b2World* world;

        b2BodyDef bodydef;
        b2Body* body;
        b2PolygonShape box;
        b2FixtureDef fixturedef;

        sf::Texture texture;
        sf::Sprite sprite;

        bool destroyed;
};

#endif // DYNAMICELEMENT_HPP_INCLUDED
