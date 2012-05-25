/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file Enemy.hpp
 * @brief Déclaration des ennemis
 *
 * Ce fichier déclare la classe Enemy représentant de manière
 * générique les ennemis du jeu.
 */

#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#include "Mob.hpp"

class Enemy : public Mob
{
    public:
        Enemy(b2World*,float32,float32,int,std::string texturePath="default",sf::IntRect subRect=sf::IntRect(2,2,16,27));
        void Render(sf::RenderWindow*);
        void Sense(Mob* mob);
        void UnSense(Mob* mob);
        void IA(b2Vec2 playerPosition);
        ~Enemy();

    protected:
        int iaType;
        int iaTimer;
        b2CircleShape radar;
        b2FixtureDef radarFixture;
        std::vector<Mob*> mobsInRange;
};



#endif // ENEMY_HPP_INCLUDED
