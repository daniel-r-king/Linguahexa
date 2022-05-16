#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <vector>
#include <string>

enum Directions {
    UP,
    UP_RIGHT,
    DOWN_RIGHT,
    DOWN,
    DOWN_LEFT,
    UP_LEFT
};

const std::string TILE_SPACE = "T";

const std::string BUILDABLE_SPACE = ".";
const std::string BLOCKED_SPACE = ".";

const int MAX_TILES_IN_PUZZLE = 20;

const int MAX_BUILD_ATTEMPTS = 1000;

const int MAX_WORD_LENGTH = 7;
const int MIN_WORD_LENGTH = 3;

const int N_SIDES_ON_TILE = 6;

const char letters[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

const int BOARD_MAX_HEIGHT = 15;
const int BOARD_MAX_WIDTH = 15;

#endif // CONSTANTS_H
