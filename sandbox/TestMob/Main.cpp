#include "Game.hpp";

int main(int argc, char** argv) {

    Game* game;
    int play=1;

    while(play) {
        game = new Game();
        play = game->Run();
        usleep(1000000);
    }

    return 0;
}
