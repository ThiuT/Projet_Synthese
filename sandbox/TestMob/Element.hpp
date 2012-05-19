#ifndef ELEMENT_HPP_INCLUDED
#define ELEMENT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include <string>
#include <cmath>

class Element {

    public:
        std::string GetID();

    protected:
        std::string ID;
};

#endif // ELEMENT_HPP_INCLUDED
