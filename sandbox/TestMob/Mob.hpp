#ifndef MOB_HPP_INCLUDED
#define MOB_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>
#include <stdio.h>

class Mob
{
    public:
        Mob(b2World*,float32,float32);
        void Render(sf::RenderWindow*);

    private:
        b2BodyDef bodydef;
        b2Body* body;
        b2PolygonShape box;
        b2FixtureDef fixturedef;

        sf::Texture texture;
        sf::Sprite sprite;
};

#endif // MOB_HPP_INCLUDED
