#ifndef PLATFORM_HPP_INCLUDED
#define PLATFORM_HPP_INCLUDED

#include "StaticElement.hpp"

class Platform : public StaticElement
{
    public:
        Platform(b2World*,float32,float32,float32,float32);
};


#endif // PLATFORM_HPP_INCLUDED
