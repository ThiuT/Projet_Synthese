#include <stdio.h>
#include <time.h>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "DebugDraw.h"
#include "Mob.hpp"

int main(int argc, char** argv) {

    // Création d'une fenêtre SFML de 800*600px et 32bits par pixel
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800,600,32),"Test");
    window->EnableKeyRepeat(false);
    // Attribution d'une position fixe à la fenêtre
    window->SetPosition(74,155);
    // Création d'un gestionnaire d'évennements SFML
    sf::Event sfmlEvent;

    // Définition des propriétés d'un monde Box2D
    b2Vec2 gravity(0.0f, -0.98f);
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    float32 timestep = 1.0f/60.0f; // = 60Hz

    // Création d'un monde Box2D
    b2World world(gravity);
    world.SetAllowSleeping(true);

    // Création du "plancher"
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(4.0f, 0.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(5.0f, 0.5f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Création d'un mob
    Mob mob(&world,1.0f,4.0f);

    // Création et assignation d'un renderer pour les objets Box2D
    DebugDraw* debugDraw;
    debugDraw = new DebugDraw(window);
    debugDraw->AppendFlags(b2Draw::e_shapeBit);
    world.SetDebugDraw(debugDraw);

    // Boucle principale : tant que la fenêtre est ouverte
    while(window->IsOpen()) {
        window->Clear();
        // Traitement des événements
        while(window->PollEvent(sfmlEvent)) {
            if(sfmlEvent.Type == sf::Event::Closed) window->Close();
            if(sfmlEvent.Type == sf::Event::KeyPressed) {
                switch(sfmlEvent.Key.Code) {
                    case sf::Keyboard::Up:
                        mob.Jump();
                        break;
                    default:
                        break;
                }
            }
        }

        if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))
            mob.Move(Mob::LEFT);
        if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Right))
            mob.Move(Mob::RIGHT);

        world.Step(timestep,velocityIterations,positionIterations);

        world.DrawDebugData();
        mob.Render(window);

        window->Display();
        usleep(3000);
    }

    return 0;
}
