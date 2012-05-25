/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file InteractiveDecor.hpp
 * @brief Déclaration des décors interactifs
 *
 * Ce fichier déclare la classe InteractiveDecor, représentant
 * les décors avec lesquels ils est possible d'intéragir.
 */

#ifndef INTERACTIVEDECOR_HPP_INCLUDED
#define INTERACTIVEDECOR_HPP_INCLUDED

#include "StaticElement.hpp"

class InteractiveDecor : public StaticElement
{
    public:
        // Types
        static const int LADDER = 1;
        static const int FINISH = 2;
        static const int SWITCH = 3;

        InteractiveDecor(b2World*,float32,float32,float32,float32,int);
        int GetType();

    protected:
            int type;
};

#endif // INTERACTIVEDECOR_HPP_INCLUDED
