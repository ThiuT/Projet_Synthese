#ifndef MOB_HPP_INCLUDED
#define MOB_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>
#include <stdio.h>

class Mob
{
    public:
        static const int LEFT = -1;
        static const int RIGHT = 1;
        static const int STOP = 0;

        Mob(b2World*,float32,float32);
        void Render(sf::RenderWindow*);
        void Move(int dir);
        void Jump();
        bool IsOnGround();

    private:
        b2BodyDef bodydef;
        b2Body* body;
        b2PolygonShape box;
        b2FixtureDef fixturedef;

        sf::Texture texture;
        sf::Sprite sprite;

        bool isMoving;
};

#endif // MOB_HPP_INCLUDED
