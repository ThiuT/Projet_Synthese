/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file Element.hpp
 * @brief Déclaration de l'élément générique
 *
 * Un élément générique n'a qu'un attribut : l'énumération
 * des types qu'il peut prendre.
 */

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
        enum categories {
            PLATFORM = 0x0001,
            CHARACTER = 0x0002,
            ENEMY = 0x0004,
            RADAR = 0x0008,
            INTERACTIVE = 0x0010,
            WEAPON = 0x0020,
            ALL = 0x003F
        };
};

#endif // ELEMENT_HPP_INCLUDED
