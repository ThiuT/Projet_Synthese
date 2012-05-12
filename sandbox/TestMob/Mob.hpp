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

        Mob(b2World*,float32,float32,string,sf::IntRect);

        void Move(int dir);
        void Jump(b2Vec2 vec,bool force=false);
        void AllowJump(bool);

    protected:
        bool canJump;
};

#endif // MOB_HPP_INCLUDED
