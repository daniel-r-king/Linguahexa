//
//  tests.cpp
//  Linguahexa
//
//  Created by Daniel R. King on 5/16/22.
//

#include <iostream>
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
    return pass;
}

bool TEST_validateCoordinates() {
    Game game;
    bool pass = true;
    if (game.validateCoordinates(BOARD_MAX_WIDTH, BOARD_MAX_HEIGHT)) {
        pass = false;
    }
    if (!game.validateCoordinates(BOARD_MAX_WIDTH - 1, BOARD_MAX_HEIGHT)) {
        pass = false;
    }
    if (!game.validateCoordinates(BOARD_MAX_WIDTH, BOARD_MAX_HEIGHT - 1)) {
        pass = false;
    }
    if (game.validateCoordinates(0, 0)) {
        pass = false;
    }
    if (!game.validateCoordinates(0, 1)) {
        pass = false;
    }
    if (!game.validateCoordinates(1, 0)) {
        pass = false;
    }
    return pass;
}

bool TEST_outOfBounds() {
    Game game;
    bool pass = true;
    int r = BOARD_MAX_HEIGHT - 1;
    int c = BOARD_MAX_WIDTH - 2;
    int length = 1;
    std::vector<int> directions = { 0, 1, 2, 3, 4, 5 };
    for (int i = 0; i < (int)directions.size(); i++) {
        if (game.outOfBounds(r, c, length, directions[i])) {
            pass = false;
            std::cout << "TEST_outOfBounds() failed at line 68" << std::endl;
            std::cout << "r = " << r << std::endl;
            std::cout << "c = " << c << std::endl;
            std::cout << "length = " << length << std::endl;
            std::cout << "direction = " << directions[i] << std::endl;
        }
    }
    r = BOARD_MAX_HEIGHT - 2;
    c = BOARD_MAX_WIDTH - 1;
    length = 1;
    for (int i = 0; i < (int)directions.size(); i++) {
        if (game.outOfBounds(r, c, length, directions[i])) {
            pass = false;
            std::cout << "TEST_outOfBounds() failed at line 81" << std::endl;
            std::cout << "r = " << r << std::endl;
            std::cout << "c = " << c << std::endl;
            std::cout << "length = " << length << std::endl;
            std::cout << "direction = " << directions[i] << std::endl;
        }
    }
    r = 0;
    c = 1;
    for (int i = 0; i < (int)directions.size(); i++) {
        if (game.outOfBounds(r, c, length, directions[i])) {
            pass = false;
            std::cout << "TEST_outOfBounds() failed at line 92" << std::endl;
            std::cout << "r = " << r << std::endl;
            std::cout << "c = " << c << std::endl;
            std::cout << "length = " << length << std::endl;
            std::cout << "direction = " << directions[i] << std::endl;
        }
    }
    r = 1;
    c = 0;
    for (int i = 0; i < (int)directions.size(); i++) {
        if (game.outOfBounds(r, c, length, directions[i])) {
            pass = false;
            std::cout << "TEST_outOfBounds() failed at line 105" << std::endl;
            std::cout << "r = " << r << std::endl;
            std::cout << "c = " << c << std::endl;
            std::cout << "length = " << length << std::endl;
            std::cout << "direction = " << directions[i] << std::endl;
        }
    }
    return pass;
}

void TEST_runTests() {
    if (TEST_boardIsEmpty()) {
        std::cout << "TEST_boardIsEmpty() passed." << std::endl;
    }
    else {
        std::cout << "TEST_boardIsEmpty() failed." << std::endl;
    }
    if (TEST_placeContiguousTiles()) {
        std::cout << "TEST_placeContiguousTiles() passed." << std::endl;
    }
    else {
        std::cout << "TEST_placeContiguousTiles() failed." << std::endl;
    }
    if (TEST_validateCoordinates()) {
        std::cout << "TEST_validateCoordinates() passed." << std::endl;
    }
    else {
        std::cout << "TEST_validateCoordinates() failed." << std::endl;
    }
    if (TEST_outOfBounds()) {
        std::cout << "TEST_outOfBounds() passed." << std::endl;
    }
    else {
        std::cout << "TEST_outOfBounds() failed." << std::endl;
    }
}
