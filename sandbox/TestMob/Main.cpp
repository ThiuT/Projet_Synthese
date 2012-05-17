#include "Game.hpp";

int main(int argc, char** argv) {

    Game game;
    int play;

    do {
        game.Initialize();
        play = game.Run();
        usleep(1000000);
    } while(play>0);

    return 0;
}
