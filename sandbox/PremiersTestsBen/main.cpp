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
    
    // Définition des propriétés d'un monde Box2D
    b2Vec2 gravity(0.0f, -0.98f);
    int32 velocityIterations = 10;
    int32 positionIterations = 3;
    //int32 scale = 30;
    float32 timestep = 1.0f/60.0f; // = 60Hz

    // Création d'un monde Box2D
    b2World* world = new b2World(gravity);
    world->SetAllowSleeping(true);
    
    // Création du "plancher"
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(4.0f,0.0f);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(3.0f, 0.5f);
    groundBody->CreateFixture(&groundBox, 0.0f);
    
    // Création d'un corps dans le monde
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(2.0f, 4.0f);
    b2Body* body = world->CreateBody(&bodyDef);
    
    // Association d'une forme de polygone à ce corps
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.2f,0.2f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    
    // Création et assignation d'un renderer pour les objets Box2D
    DebugDraw* debugDraw;
    debugDraw = new DebugDraw(window);
    debugDraw->AppendFlags(b2Draw::e_shapeBit);
    world->SetDebugDraw(debugDraw);
    
   
    // Boucle principale : tant que la fenêtre est ouverte
    while(window->IsOpen()) {
        window->Clear();
        // Traitement des événements
        while(window->PollEvent(sfmlEvent)) {
            if(sfmlEvent.Type == sf::Event::Closed) window->Close();
        }
        world->Step(timestep,velocityIterations,positionIterations);
        
        
        world->DrawDebugData();
        
        //b2Vec2 position = body->GetPosition();
        //float32 angle = body->GetAngle();
        //printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
       
        window->Display();
    }
    
    delete world;
    return 0;
}

