#ifndef DYNAMICELEMENT_HPP_INCLUDED
#define DYNAMICELEMENT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include <string>

class DynamicElement
{
    public:
        DynamicElement(b2World*,float32,float32,bool);
        void Render(sf::RenderWindow*);
        int GetID();
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

        int ID;
        bool destroyed;
};

#endif // DYNAMICELEMENT_HPP_INCLUDED
