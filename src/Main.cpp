/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file Main.cpp
 * @brief Programme principal
 *
 * Ce fichier contient la fonction principale du programme
 */

#include "Game.hpp";

/** @brief Fonction principale
 *
 * La fonction principale du jeu est une boucle :
 *  - initialiser une instance du jeu
 *  - lancer le jeu
 *  - répéter tant que la valeur de retour est positive
 * (le jeu renvoie le nombre de vies restantes, 0 en cas d'arrêt brutal)
 */
int main(int argc, char** argv) {

    Game game;
    int play;

    do {
        game.Initialize();
        play = game.Run();
        usleep(500000);
    } while(play>0);

    return 0;
}
