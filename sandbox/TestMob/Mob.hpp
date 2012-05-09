#ifndef MOB_HPP_INCLUDED
#define MOB_HPP_INCLUDED

#include "DynamicElement.hpp"

using namespace std;

class Mob : public DynamicElement
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

        void Move(int dir);
        void Jump(b2Vec2 vec,bool force=false);
        bool IsOnGround();
};

#endif // MOB_HPP_INCLUDED
