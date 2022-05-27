#include <iostream>
#include <random>
#include <chrono>
#include "game.hpp"
#include "constants.hpp"
#include "tests.hpp"

int main() {
    std::srand(time(0));
    TEST_runTests();
    Game game;
    game.printBoard();
    bool gameIsOver = false;
    while (!gameIsOver) {
        game.printMenu();
        bool inputValid = false;
        while (!inputValid) {
            int input = 2;
            std::cin >> input;
            switch (input) {
            case 1: {
                inputValid = true;
                std::string letter = game.getLetter();
                int r = game.getRow();
                int c = game.getColumn();
                game.placeTile(letter, r, c);
                game.printBoard();
                break;
            }
            case 2: {
                inputValid = true;
                int fr = game.getRow();
                int fc = game.getColumn();
                int tr = game.getRow();
                int tc = game.getColumn();
                game.moveTile(fr, fc, tr, tc);
                game.printBoard();
                break;
            }
            case 3: {
                inputValid = true;
                int r = game.getRow();
                int c = game.getColumn();
                game.removeTile(r, c);
                game.printBoard();
                break;
            }
            case 4: {
                inputValid = true;
                game.linkTiles();
                game.constructWordSlots();
                if (game.puzzleIsCoherent()) {
                    std::cout << "The puzzle is coherent." << std::endl;
                }
                else {
                    std::cout << "The puzzle is not coherent." << std::endl;
                }
                game.printBoard();
                break;
            }
            case 5: {
                inputValid = true;
                return 0;
                break;
            }
            default: {
                std::cout << "Invalid input detected..." << std::endl;
            }
            }
        }
    }

    return 0;
}
