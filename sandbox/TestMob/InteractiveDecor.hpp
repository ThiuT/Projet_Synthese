#ifndef INTERACTIVEDECOR_HPP_INCLUDED
#define INTERACTIVEDECOR_HPP_INCLUDED

#include "StaticElement.hpp"

class InteractiveDecor : public StaticElement
{
    public:
        // Types
        static const int LADDER = 1;
        static const int FINISH = 2;

        InteractiveDecor(b2World*,float32,float32,float32,float32,int);
        int GetType();

    protected:
            int type;
};

#endif // INTERACTIVEDECOR_HPP_INCLUDED
