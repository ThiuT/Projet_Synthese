#ifndef MOB_HPP_INCLUDED
#define MOB_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include <string>

using namespace std;

class Mob
{
    public:
        // Directions
        static const int LEFT = -1;
        static const int RIGHT = 1;
        static const int STOP = 0;

        // Permissions
        static const int CLIMB = 0x01;

        // Identifiants de type
        static const int CHARACTER = 1;
        static const int ENEMY = 2;

        Mob(b2World*,float32,float32,string,sf::IntRect);
        void Render(sf::RenderWindow*);
        void Move(int dir);
        void Jump(b2Vec2 vec,bool force=false);
        bool IsOnGround();
        int GetID();
        bool IsDead();
        void SetDead(bool);
        ~Mob();

    protected:
        b2World* world;

        b2BodyDef bodydef;
        b2Body* body;
        b2PolygonShape box;
        b2FixtureDef fixturedef;

        sf::Texture texture;
        sf::Sprite sprite;

        int ID;
        bool dead;
};

#endif // MOB_HPP_INCLUDED
