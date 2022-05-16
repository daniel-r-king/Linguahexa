//
//  tests.cpp
//  Linguahexa
//
//  Created by Daniel R. King on 5/16/22.
//

#include "tests.hpp"
#include "game.hpp"
#include "tile.hpp"
#include "word.hpp"
#include "constants.hpp"

bool TEST_boardIsEmpty() {
    bool pass = true;
    Game game;
    game.board[BOARD_MAX_HEIGHT / 2][BOARD_MAX_WIDTH / 2] = TILE_SPACE;
    if (game.boardIsEmpty()) {
        pass = false;
    }
    game.board[BOARD_MAX_HEIGHT / 2][BOARD_MAX_WIDTH / 2] = BUILDABLE_SPACE;
    if (!game.boardIsEmpty()) {
        pass = false;
    }
    return pass;
}

bool TEST_placeContiguousTiles() {
    bool pass = true;
    Game game;
    int r = BOARD_MAX_HEIGHT / 2;
    int c = (BOARD_MAX_WIDTH / 2) + 1;
    int length = MAX_WORD_LENGTH;
    int direction = UP;
    if (!game.placeContiguousTiles(r, c, length, direction)) {
        std::cout << "Game::placeContiguousTiles test failed at line 35." << std::endl;
        std::cout << r << std::endl;
        std::cout << c << std::endl;
        std::cout << length << std::endl;
        std::cout << direction << std::endl;
        game.printBoard();
        pass = false;
    }
    game.board.clear();
    r = BOARD_MAX_HEIGHT;
    c = BOARD_MAX_WIDTH;
    length = 2;
    direction = DOWN_RIGHT;
    if (game.placeContiguousTiles(r, c, length, direction)) {
        std::cout << "Game::placeContiguousTiles test failed at line 49." << std::endl;
        std::cout << r << std::endl;
        std::cout << c << std::endl;
        std::cout << length << std::endl;
        std::cout << direction << std::endl;
        game.printBoard();
        pass = false;
    }
    game.board.clear();
    r = 0;
    c = 0;
    length = 1;
    direction = UP_LEFT;
    if (!game.placeContiguousTiles(r, c, length, direction)) {
        std::cout << "Game::placeContiguousTiles test failed at line 64." << std::endl;
        std::cout << r << std::endl;
        std::cout << c << std::endl;
        std::cout << length << std::endl;
        std::cout << direction << std::endl;
        game.printBoard();
        pass = false;
    }
    game.board.clear();
    r = BOARD_MAX_HEIGHT;
    c = BOARD_MAX_WIDTH;
    length = 1;
    direction = DOWN_RIGHT;
    if (!game.placeContiguousTiles(r, c, length, direction)) {
        std::cout << "Game::placeContiguousTiles test failed at line 78." << std::endl;
        std::cout << r << std::endl;
        std::cout << c << std::endl;
        std::cout << length << std::endl;
        std::cout << direction << std::endl;
        game.printBoard();
        pass = false;
    }
    game.board.clear();
    r = INT_MAX;
    c = INT_MAX;
    length = 1;
    direction = 0;
    if (!game.placeContiguousTiles(r, c, length, direction)) {
        std::cout << "Game::placeContiguousTiles test failed at line 92." << std::endl;
        std::cout << r << std::endl;
        std::cout << c << std::endl;
        std::cout << length << std::endl;
        std::cout << direction << std::endl;
        game.printBoard();
        pass = false;
    }
    game.board.clear();
    r = BOARD_MAX_HEIGHT;
    c = BOARD_MAX_WIDTH;
    length = 1;
    direction = DOWN_RIGHT;
    if (!game.placeContiguousTiles(r, c, length, direction)) {
        std::cout << "Game::placeContiguousTiles test failed at line 78." << std::endl;
        std::cout << r << std::endl;
        std::cout << c << std::endl;
        std::cout << length << std::endl;
        std::cout << direction << std::endl;
        game.printBoard();
        pass = false;
    }
    return pass;
}

void TEST_runTests() {
    if (TEST_boardIsEmpty()) {
        std::cout << "TEST_boardIsEmpty() passed." << std::endl;
    }
    if (TEST_placeContiguousTiles()) {
        std::cout << "TEST_placeContiguousTiles() passed" << std::endl;
    }
}
