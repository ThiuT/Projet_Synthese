#ifndef SWITCH_HPP_INCLUDED
#define SWITCH_HPP_INCLUDED

#include "InteractiveDecor.hpp"

class Switch : public InteractiveDecor
{
    public:
        Switch(float32,float32,StaticElement*);
        void Action();
        ~Switch();

    protected:
        StaticElement* target;
};

#endif // SWITCH_HPP_INCLUDED
