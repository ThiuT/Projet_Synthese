/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file Game.hpp
 * @brief Déclaration du jeu
 *
 * Ce fichier déclare la classe Game, correspondant à une instance du jeu.
 */

#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include <string.h>
#include "DebugDraw.h"
#include "Character.hpp"
#include "Enemy.hpp"
#include "CollisionManager.hpp"
#include "Platform.hpp"
#include "InteractiveDecor.hpp"
#include "FlyingEnemy.hpp"

class Game {

    private:
        // Attributs SFML
        sf::RenderWindow* window;
        sf::View view;
        sf::Event sfmlEvent;
        b2World* world;

        // Attributs du monde
        b2Vec2 gravity;
        int32 velocityIterations;
        int32 positionIterations;
        float32 timeStep;

        // Gesionnaire de collisions
        CollisionManager* cMng;

        // Listes
        Character* player;
        std::vector<Enemy*> enemies;
        std::vector<StaticElement*> map;

        int lives;
        sf::Thread mobsIA;

        sf::Sprite background;
        sf::Texture bgtexture;

    public:
        Game();
        void Initialize();
        void CreateLevel();
        int Run();
        void UpdateMobs();
        int Terminate(int);

};

#endif // GAME_HPP_INCLUDED
