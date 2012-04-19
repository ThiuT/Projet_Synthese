/* 
 * File:   main.cpp
 * Author: thiut
 * 
 * Inspired by video : http://www.youtube.com/watch?v=LgVsYTsXeIA
 *
 * Created on 7 avril 2012, 15:56
 */

#include <stdio.h>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "DebugDraw.h"

int main(int argc, char** argv) {
    
    // Création d'une fenêtre SFML de 800*600px et 32bits par pixel 
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800,600,32),"Test");
    // Attribution d'une position fixe à la fenêtre
    window->SetPosition(74,155);
    // Création d'un gestionnaire d'évennements SFML
    sf::Event sfmlEvent;
    // Création d'une boite SFML et initialisation
    sf::RectangleShape box;
    box.SetPosition(100,100);
    box.SetSize(sf::Vector2f(50,50));
    box.SetFillColor(sf::Color::Red);
    
    // Création d'une texture (chargement d'une image en mémoire)
    sf::Texture texture;
    if(!texture.LoadFromFile("smiley.png")) return EXIT_FAILURE;
    // Création d'un sprite matérialisant la texture
    sf::Sprite sprite;
    sprite.SetTexture(texture);
    sprite.SetPosition(400,400);
    
    // Définition des propriétés d'un monde Box2D
    b2Vec2 gravity(0.0f, -10.0f);
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    int32 scale = 30;
    float32 timestep = 1.0f/60.0f; // = 60Hz

    // Création d'un monde Box2D
    b2World world(gravity);
    world.SetAllowSleeping(true);
    
    // Création du "plancher"
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);
    
    // Création d'un corps dans le monde
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&bodyDef);
    
    // Association d'une forme de polygone à ce corps
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f,1.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    
    // Création et assignation d'un renderer pour les objets Box2D
    DebugDraw* debugDraw;
    debugDraw = new DebugDraw(window);
    world.SetDebugDraw(debugDraw);
   
    // Boucle principale : tant que la fenêtre est ouverte
    while(window->IsOpen()) {
        window->Clear();
        // Traitement des événements
        while(window->PollEvent(sfmlEvent)) {
            if(sfmlEvent.Type == sf::Event::Closed) window->Close();
        }
        window->Draw(box);
        window->Draw(sprite);
        world.DrawDebugData();
        
        window->Display();
    }
    
    return 0;
}

