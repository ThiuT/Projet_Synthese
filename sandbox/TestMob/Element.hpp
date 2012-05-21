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
        enum categories {
            PLATFORM = 0x0001,
            CHARACTER = 0x0002,
            ENEMY = 0x0004,
            RADAR = 0x0008,
            INTERACTIVE = 0x0010,
            ALL = 0x001F
        };

    protected:
        std::string ID;
};

#endif // ELEMENT_HPP_INCLUDED
