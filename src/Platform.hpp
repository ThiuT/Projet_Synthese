/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file Platform.hpp
 * @brief Déclaration des plates-formes
 *
 * Ce fichier déclare la classe Platform, représentant
 * les plates-formes fixes du jeu.
 */

#ifndef PLATFORM_HPP_INCLUDED
#define PLATFORM_HPP_INCLUDED

#include "StaticElement.hpp"

class Platform : public StaticElement
{
    public:
        Platform(b2World*,float32,float32,float32,float32,std::string,bool);
        bool IsCloud();

    protected:
        bool cloud;
};


#endif // PLATFORM_HPP_INCLUDED
