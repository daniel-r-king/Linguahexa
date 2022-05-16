#include <iostream>
#include <random>
#include <chrono>
#include "game.hpp"
#include "constants.hpp"

int main() {
    std::srand(time(0));
    Game game;
    bool puzzleBuilt = false;
    while (!puzzleBuilt) {
        game.clear();
        game.arrangeBoard();
        game.placeTiles();
        game.linkTiles();
        game.constructWordSlots();

        int counter = 0;
        for (unsigned int i = 0; i < game.wordSlots.size(); i++) {
            if (game.wordSlots[i].length == 2) {
                counter++;
            }
        }
        while (counter > 1) {
            game.clear();
            game.arrangeBoard();
            game.placeTiles();
            game.linkTiles();
            game.constructWordSlots();
            counter = 0;
            for (unsigned int i = 0; i < game.wordSlots.size(); i++) {
                if (game.wordSlots[i].length == 2) {
                    counter++;
                }
            }
        }

        int runs = 0;
        bool puzzleCoherent = false;
        while (!puzzleCoherent && runs < MAX_BUILD_ATTEMPTS) {
            game.placeWordsAtRandom();
            puzzleCoherent = game.puzzleIsCoherent();
            if (puzzleCoherent) {
                puzzleBuilt = true;
            }
            runs++;
        }
        std::cout << runs << std::endl;
        game.printBoard();
    }

    for (unsigned int i = 0; i < game.wordSlots.size(); i++) {
        std::cout << game.wordSlots[i].word << std::endl;
    }

    return 0;
}
