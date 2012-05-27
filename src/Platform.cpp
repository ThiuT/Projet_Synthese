/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file Platform.cpp
 * @brief Implémentation des plates-formes
 *
 * Ce fichier implémente les méthodes de la classe Platform
 */

#include "Platform.hpp"

/** @brief Constructeur
 *
 * Appelle le constructeur de StaticElement à la position voulue, crée la forme
 * et la composante graphique.
 *
 * @param world : pointeur vers le monde Box2D
 * @param x : position initiale x
 * @param y : position initiale y
 * @param width : largeur
 * @param height : hauteur
 * @param texturePath : chemin d'accès à la texture
 * @param isCloud : drapeau permettant de marquer les clouds
 */
Platform::Platform(b2World* world, float32 x, float32 y, float32 width, float32 height, std::string texturePath, bool isCloud) : StaticElement(world,x,y)
{
    texture.LoadFromFile(texturePath);
    texture.SetRepeated(true);
    sprite.SetTexture(texture);
    sprite.SetTextureRect(sf::IntRect(0,0,width*200,height*200));
    sprite.SetOrigin(sprite.GetLocalBounds().Width/2.0f,sprite.GetLocalBounds().Height/2.0f);

    box.SetAsBox(width,height);
    fixturedef.shape = &box;
    fixturedef.density = 1.0f;
    fixturedef.friction = 1.0f;
    body->CreateFixture(&fixturedef);

    cloud = isCloud;
    body->SetUserData(this);
}

/** @brief Test cloud
 *
 * Permet de savoir si la plate forme est un cloud.
 */
bool Platform::IsCloud()
{
    return cloud;
}


