#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include <string.h>
#include "DebugDraw.h"
#include "Mob.hpp"
#include "Character.hpp"
#include "Enemy.hpp"

class Game {

    private:
        // Attributs SFML
        sf::RenderWindow* window;
        sf::Event sfmlEvent;
        b2World* world;

        // Attributs du monde
        b2Vec2 gravity;
        int32 velocityIterations;
        int32 positionIterations;
        float32 timeStep;

        // Listes
        Character* player;
        std::vector<Enemy*> mobs;

    public:
        Game();
        void Initialize();
        void Run();
};

#endif // GAME_HPP_INCLUDED
