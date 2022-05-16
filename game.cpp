#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <random>
#include <ctime>
#include <chrono>
#include <vector>
#include "constants.hpp"
#include "game.hpp"
#include "tile.hpp"
#include "word.hpp"

Game::Game() {
    for (int i = 0; i < BOARD_MAX_HEIGHT; i++) {
        std::vector<std::string> strings;
        for (int j = 0; j < BOARD_MAX_WIDTH; j++) {
            strings.push_back(BUILDABLE_SPACE);
        }
        board.push_back(strings);
    }
}

Game::~Game() {
}

std::vector<std::vector<std::string>> Game::backupBoard() {
    std::vector<std::vector<std::string>> temp;
    for (int i = 0; i < BOARD_MAX_HEIGHT; i++) {
        std::vector<std::string> strings;
        for (int j = 0; j < BOARD_MAX_WIDTH; j++) {
            strings.push_back(board[i][j]);
        }
        temp.push_back(strings);
    }
    return temp;
}

bool Game::boardIsEmpty() {
    for (unsigned int i = 0; i < BOARD_MAX_HEIGHT; i++) {
        for (unsigned int j = 0; j < BOARD_MAX_WIDTH; j++) {
            if (board[i][j] == TILE_SPACE) {
                return false;
            }
        }
    }
    return true;
}


bool Game::placeContiguousTiles(int r, int c, int length, int direction) {
    if (outOfBounds(r, c, length, direction)) {
        return false;
    }
    bool connectionDetected = boardIsEmpty();
    std::vector<std::vector<std::string>> temp = backupBoard();
    switch (direction) {
    case 0:
        for (int i = 0; i < length; i++) {
            if (board[r - (i * 2)][c] == TILE_SPACE) {
                connectionDetected = true;
            }
            board[r - (i * 2)][c] = TILE_SPACE;
        }
        break;
    case 1:
        for (int i = 0; i < length; i++) {
            if (board[r - i][c + i] == TILE_SPACE) {
                connectionDetected = true;
            }
            board[r - i][c + i] = TILE_SPACE;
        }
        break;
    case 2:
        for (int i = 0; i < length; i++) {
            if (board[r + i][c + i] == TILE_SPACE) {
                connectionDetected = true;
            }
            board[r + i][c + i] = TILE_SPACE;
        }
        break;
    case 3:
        for (int i = 0; i < length; i++) {
            if (board[r + (i * 2)][c] == TILE_SPACE) {
                connectionDetected = true;
            }
            board[r + (i * 2)][c] = TILE_SPACE;
        }
        break;
    case 4:
        for (int i = 0; i < length; i++) {
            if (board[r + i][c - i] == TILE_SPACE) {
                connectionDetected = true;
            }
            board[r + i][c - i] = TILE_SPACE;
        }
        break;
    case 5:
        for (int i = 0; i < length; i++) {
            if (board[r - i][c - i] == TILE_SPACE) {
                connectionDetected = true;
            }
            board[r - i][c - i] = TILE_SPACE;
        }
        break;
    }
    if (!connectionDetected) {
        board = temp;
    }
    return connectionDetected;
}

bool Game::placeBaseTiles(int r, int c, int length, int direction) {
    if (outOfBounds(r, c, length, direction)) {
        return false;
    }
    switch (direction) {
    case 0:
        for (int i = 0; i < length; i++) {
            board[r - (i * 2)][c] = TILE_SPACE;
        }
        break;
    case 1:
        for (int i = 0; i < length; i++) {
            board[r - i][c + i] = TILE_SPACE;
        }
        break;
    case 2:
        for (int i = 0; i < length; i++) {
            board[r + i][c + i] = TILE_SPACE;
        }
        break;
    case 3:
        for (int i = 0; i < length; i++) {
            board[r + (i * 2)][c] = TILE_SPACE;
        }
        break;
    case 4:
        for (int i = 0; i < length; i++) {
            board[r + i][c - i] = TILE_SPACE;
        }
        break;
    case 5:
        for (int i = 0; i < length; i++) {
            board[r - i][c - i] = TILE_SPACE;
        }
        break;
    }
    return true;
}

bool Game::outOfBounds(int r, int c, int length, int direction) {
    switch (direction) {
    case 0:
        if (r - (length * 2 ) < 0) {
            return true;
        }
        break;
    case 1:
        if (r - length < 0 | c + length > BOARD_MAX_HEIGHT) {
            return true;
        }
        break;
    case 2:
        if (r + length > 0 | c + length > BOARD_MAX_HEIGHT) {
            return true;
        }
        break;
    case 3:
        if (r + (length * 2) > BOARD_MAX_WIDTH) {
            return true;
        }
        break;
    case 4:
        if (r + length > BOARD_MAX_WIDTH | c - length < 0) {
            return true;
        }
        break;
    case 5:
        if (r - length < 0 | c - length < 0) {
            return true;
        }
        break;
    }
    return false;
}

bool Game::validateCoordinates(int r, int c) {
    if ((r % 2 == 0 && c % 2 != 0) | (r % 2 != 0 && c % 2 == 0)) {
        return true;
    } else {
        return false;
    }
}

void Game::placeTiles() {
    for (int i = 0; i < BOARD_MAX_HEIGHT; i++) {
        for (int j = 0; j < BOARD_MAX_WIDTH; j++) {
            if (board[i][j] == TILE_SPACE) {
                Tile tile(" ", i, j);
                gameTiles.push_back(tile);
            }
        }
    }
}

void Game::linkTiles() {
    for (unsigned int i = 0; i < gameTiles.size(); i++) {
        for (unsigned int j = 0; j < gameTiles.size(); j++) {
            int ir = gameTiles[i].r;
            int jr = gameTiles[j].r;
            int ic = gameTiles[i].c;
            int jc = gameTiles[j].c;
            // up
            if (jr == ir - 2 && jc == ic) {
                gameTiles[i].s[0] = &gameTiles[j];
            }
            // up_right
            if (jr == ir - 1 && jc == ic + 1) {
                gameTiles[i].s[1] = &gameTiles[j];
            }
            // down_right
            if (jr == ir + 1 && jc == ic + 1) {
                gameTiles[i].s[2] = &gameTiles[j];
            }
            // down
            if (jr == ir + 2 && jc == ic) {
                gameTiles[i].s[3] = &gameTiles[j];
            }
            // down_left
            if (jr == ir + 1 && jc == ic - 1) {
                gameTiles[i].s[4] = &gameTiles[j];
            }
            // up_left
            if (jr == ir -1 && jc == ic - 1) {
                gameTiles[i].s[5] = &gameTiles[j];
            }
        }
    }
}

void Game::clear() {
    gameTiles.clear();
    wordSlots.clear();
    board.clear();
    for (int i = 0; i < BOARD_MAX_HEIGHT; i++) {
        std::vector<std::string> strings;
        for (int j = 0; j < BOARD_MAX_WIDTH; j++) {
            strings.push_back(BUILDABLE_SPACE);
        }
        board.push_back(strings);
    }
}

void Game::arrangeBoard() {
    int nTilesPlaced = 0;
    while (nTilesPlaced < MAX_TILES_IN_PUZZLE) {
        int randomR;
        int randomC;
        bool coordinatesValid = false;
        while (!coordinatesValid) {
            randomR = rand() % BOARD_MAX_HEIGHT;
            randomC = rand() % BOARD_MAX_WIDTH;
            coordinatesValid = validateCoordinates(randomR, randomC);
        }
        int length = rand() % (MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1) + MIN_WORD_LENGTH;
        int direction = rand() % N_SIDES_ON_TILE;
        while (!placeContiguousTiles(randomR, randomC, length, direction)) {
            coordinatesValid = false;
            while (!coordinatesValid) {
                randomR = rand() % BOARD_MAX_HEIGHT;
                randomC = rand() % BOARD_MAX_WIDTH;
                coordinatesValid = validateCoordinates(randomR, randomC);
            }
            length = rand() % (MAX_WORD_LENGTH - MIN_WORD_LENGTH + 1) + MIN_WORD_LENGTH;
            direction = rand() % N_SIDES_ON_TILE;
        }
        nTilesPlaced += length;
    }
}

int Game::getDistance(Tile* tile, int direction) {
    int distance = 1;
    Tile* current;
    switch (direction) {
    case 0:
        current = tile;
        while (current->s[0] != nullptr) {
            distance++;
            current = current->s[0];
        }
        break;
    case 1:
        current = tile;
        while (current->s[1] != nullptr) {
            distance++;
            current = current->s[1];
        }
        break;
    case 2:
        current = tile;
        while (current->s[2] != nullptr) {
            distance++;
            current = current->s[2];
        }
        break;
    case 3:
        current = tile;
        while (current->s[3] != nullptr) {
            distance++;
            current = current->s[3];
        }
        break;
    case 4:
        current = tile;
        while (current->s[4] != nullptr) {
            distance++;
            current = current->s[4];
        }
        break;
    case 5:
        current = tile;
        while (current->s[5] != nullptr) {
            distance++;
            current = current->s[5];
        }
        break;
    }
    return distance;
}

void Game::constructWordSlots() {
    for (unsigned int i = 0; i < gameTiles.size(); i++) {
        int length = 0;
        if (gameTiles[i].s[0] != nullptr && gameTiles[i].s[3] == nullptr) {
            length = 1;
            Word word;
            word.start = &gameTiles[i];
            Tile* current = &gameTiles[i];
            while (current->s[0] != nullptr) {
                length++;
                word.tiles.push_back(current);
                current = current->s[0];
            }
            word.length = length;
            word.direction = UP;
            word.end = current;
            word.tiles.push_back(current);
            wordSlots.push_back(word);
        }
        if (gameTiles[i].s[1] != nullptr && gameTiles[i].s[4] == nullptr) {
            length = 1;
            Word word;
            word.start = &gameTiles[i];
            Tile* current = &gameTiles[i];
            while (current->s[1] != nullptr) {
                length++;
                word.tiles.push_back(current);
                current = current->s[1];
            }
            word.length = length;
            word.direction = UP_RIGHT;
            word.end = current;
            word.tiles.push_back(current);
            wordSlots.push_back(word);
        }
        if (gameTiles[i].s[2] != nullptr && gameTiles[i].s[5] == nullptr) {
            length = 1;
            Word word;
            word.start = &gameTiles[i];
            Tile* current = &gameTiles[i];
            while (current->s[2] != nullptr) {
                length++;
                word.tiles.push_back(current);
                current = current->s[2];
            }
            word.length = length;
            word.direction = DOWN_RIGHT;
            word.end = current;
            word.tiles.push_back(current);
            wordSlots.push_back(word);
        }
        if (gameTiles[i].s[3] != nullptr && gameTiles[i].s[0] == nullptr) {
            length = 1;
            Word word;
            word.start = &gameTiles[i];
            Tile* current = &gameTiles[i];
            while (current->s[3] != nullptr) {
                length++;
                word.tiles.push_back(current);
                current = current->s[3];
            }
            word.length = length;
            word.direction = DOWN;
            word.end = current;
            word.tiles.push_back(current);
            wordSlots.push_back(word);
        }
        if (gameTiles[i].s[4] != nullptr && gameTiles[i].s[1] == nullptr) {
            length = 1;
            Word word;
            word.start = &gameTiles[i];
            Tile* current = &gameTiles[i];
            while (current->s[4] != nullptr) {
                length++;
                word.tiles.push_back(current);
                current = current->s[4];
            }
            word.length = length;
            word.direction = DOWN_LEFT;
            word.end = current;
            word.tiles.push_back(current);
            wordSlots.push_back(word);
        }
        if (gameTiles[i].s[5] != nullptr && gameTiles[i].s[2] == nullptr) {
            length = 1;
            Word word;
            word.start = &gameTiles[i];
            Tile* current = &gameTiles[i];
            while (current->s[5] != nullptr) {
                length++;
                word.tiles.push_back(current);
                current = current->s[5];
            }
            word.length = length;
            word.direction = UP_LEFT;
            word.end = current;
            word.tiles.push_back(current);
            wordSlots.push_back(word);
        }
    }
    trimWordSlots();
}

void Game::trimWordSlots() {
    for (unsigned int i = 0; i < wordSlots.size(); i++) {
        for (unsigned int j = 0; j < wordSlots.size(); j++) {
            if (wordSlots[i].start == wordSlots[j].end && wordSlots[i].end == wordSlots[j].start) {
                wordSlots.erase(wordSlots.begin() + j);
            }
        }
    }
}

std::string Game::getRandomWord(int length) {
    std::ifstream input;
    std::vector<std::string> words;
    input.open("/Users/daniel/Projects/Linguahexa/Linguahexa/words.txt");
    std::string str;
    if (input.is_open()) {
        while (std::getline(input, str)) {
            if (str.length() == (unsigned int)length) {
                words.push_back(str);
            }
        }
    } else {
      std::cout << "ERROR: Failed to open input file." << std::endl;
    }
    unsigned int i = rand() % words.size();
    return words[i];
}

void Game::invertWord(Word* word) {
    int direction = word->direction;
    Tile* current = word->start;
    std::string str = word->word;
    unsigned int j = str.length() - 1;
    unsigned int i = 0;
    while (j > str.length() / 2) {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }
    word->word = str;
    switch (direction) {
    case 0:
        while (current != nullptr) {
            current->letter = word->word[j];
            j++;
            current = current->s[0];
        }
        break;
    case 1:
        while (current != nullptr) {
            current->letter = word->word[j];
            j++;
            current = current->s[1];
        }
        break;
    case 2:
        while (current != nullptr) {
            current->letter = word->word[j];
            j++;
            current = current->s[2];
        }
        break;
    case 3:
        while (current != nullptr) {
            current->letter = word->word[j];
            j++;
            current = current->s[3];
        }
        break;
    case 4:
        while (current != nullptr) {
            current->letter = word->word[j];
            j++;
            current = current->s[4];
        }
        break;
    case 5:
        while (current != nullptr) {
            current->letter = word->word[j];
            j++;
            current = current->s[5];
        }
        break;
    }
}

void Game::placeWordsAtRandom() {
    for (unsigned int i = 0; i < wordSlots.size(); i++) {
        std::string word = getRandomWord(wordSlots[i].length);
        wordSlots[i].word = word;
        Tile* current = wordSlots[i].start;
        int direction = wordSlots[i].direction;
        int j = 0;
        switch (direction) {
        case 0:
            while (current != nullptr) {
                current->letter = word[j];
                j++;
                current = current->s[0];
            }
            break;
        case 1:
            while (current != nullptr) {
                current->letter = word[j];
                j++;
                current = current->s[1];
            }
            break;
        case 2:
            while (current != nullptr) {
                current->letter = word[j];
                j++;
                current = current->s[2];
            }
            break;
        case 3:
            while (current != nullptr) {
                current->letter = word[j];
                j++;
                current = current->s[3];
            }
            break;
        case 4:
            while (current != nullptr) {
                current->letter = word[j];
                j++;
                current = current->s[4];
            }
            break;
        case 5:
            while (current != nullptr) {
                current->letter = word[j];
                j++;
                current = current->s[5];
            }
            break;
        }
    }
}

void Game::getWords(unsigned int length, char letter, int index, std::vector<std::string>* words) {
    std::fstream input;
    input.open("/Users/daniel/Projects/Linguahexa/Linguahexa/words.txt");
    std::string str;
    if (input.is_open()) {
        while (std::getline(input, str)) {
            if (str.length() == length && str[index] == letter) {
                words->push_back(str);
            }
        }
    } else {
        std::cout << "ERROR: Failed to open input file." << std::endl;
    }
}

bool Game::puzzleIsCoherent() {
    for (unsigned int i = 0; i < wordSlots.size(); i++) {
        Tile* current;
        current = wordSlots[i].start;
        std::string forward;
        std::string backward;
        switch (wordSlots[i].direction) {
        case 0:
            while (current != nullptr) {
                forward += current->letter;
                current = current->s[0];
            }
            current = wordSlots[i].end;
            while (current != nullptr) {
                backward += current->letter;
                current = current->s[3];
            }
            break;
        case 1:
            while (current != nullptr) {
                forward += current->letter;
                current = current->s[1];
            }
            current = wordSlots[i].end;
            while (current != nullptr) {
                backward += current->letter;
                current = current->s[4];
            }
            break;
        case 2:
            while (current != nullptr) {
                forward += current->letter;
                current = current->s[2];
            }
            current = wordSlots[i].end;
            while (current != nullptr) {
                backward += current->letter;
                current = current->s[5];
            }
            break;
        case 3:
            while (current != nullptr) {
                forward += current->letter;
                current = current->s[3];
            }
            current = wordSlots[i].end;
            while (current != nullptr) {
                backward += current->letter;
                current = current->s[0];
            }
            break;
        case 4:
            while (current != nullptr) {
                forward += current->letter;
                current = current->s[4];
            }
            current = wordSlots[i].end;
            while (current != nullptr) {
                backward += current->letter;
                current = current->s[1];
            }
            break;
        case 5:
            while (current != nullptr) {
                forward += current->letter;
                current = current->s[5];
            }
            current = wordSlots[i].end;
            while (current != nullptr) {
                backward += current->letter;
                current = current->s[2];
            }
            break;
        }
        if (!isAWord(forward) && !isAWord(backward)) {
            return false;
        }
    }
    return true;
}

int Game::getTileIndex(Word word, Tile* tile, int direction) {
    Tile* current = word.start;
    int i = 0;
    switch (direction) {
    case 0:
        while (current != nullptr) {
            if (tile == current) {
                return i;
            }
            i++;
            current = current->s[0];
        }
        break;
    case 1:
        while (current != nullptr) {
            if (tile == current) {
                return i;
            }
            i++;
            current = current->s[1];
        }
        break;
    case 2:
        while (current != nullptr) {
            if (tile == current) {
                return i;
            }
            i++;
            current = current->s[2];
        }
        break;
    case 3:
        while (current != nullptr) {
            if (tile == current) {
                return i;
            }
            i++;
            current = current->s[3];
        }
        break;
    case 4:
        while (current != nullptr) {
            if (tile == current) {
                return i;
            }
            i++;
            current = current->s[4];
        }
        break;
    case 5:
        while (current != nullptr) {
            if (tile == current) {
                return i;
            }
            i++;
            current = current->s[5];
        }
        break;
    }
    return -1;
}

void Game::placeWordByWord() {
    std::vector<Word> completedWords;
    for (unsigned int i = 0; i < wordSlots.size(); i++) {
        std::string word = "";
        if (i == 0) {
            // first word has no dependencies
            word = getRandomWord(wordSlots[i].length);
            wordSlots[i].word = word;

        } else {
            // go through all previously formed words, and determine which, if any, share tiles with the currently iterated word
            std::vector<Tile*> sharedTiles;
            std::vector<std::pair<std::string, int>> requiredLetters;
            for (int j = i - 1; j > -1; j--) { // going through all previously formed words
                sharedTiles = getSharedTiles(wordSlots[i], wordSlots[j]); // get tiles shared between currently iterated word and currently iterated previous word
                for (unsigned int k = 0; k < sharedTiles.size(); k++) { // go through set of tiles shared by the current two iterated words, determine the index of the shared letter in the currently iterated word
                    std::string sharedLetter = sharedTiles[k]->letter;
                    int sharedLetterIndex = getTileIndex(wordSlots[i], sharedTiles[k], wordSlots[i].direction);
                    std::pair<std::string, int> pair = { sharedLetter, sharedLetterIndex };
                    requiredLetters.push_back(pair);
                }
            }
            std::vector<std::string> words;
            for (unsigned int j = 0; j < requiredLetters.size(); j++) {
                int length = wordSlots[i].length;
                char letter = requiredLetters[j].first[0];
                int index = requiredLetters[j].second;
                getWords(length, letter, index, &words);
            }
            int k = rand() % words.size();
            word = words[k];
        }
        if (word == "") {
            for (int i = 0; i < wordSlots[i].length; i++) {
                word[i] = 't';
            }
        }
        Tile* current;
        current = wordSlots[i].start;
        int direction = wordSlots[i].direction;
        int j = 0;
        switch (direction) {
        case 0:
            while (current != nullptr) {
                current->letter = word[j];
                j++;
                current = current->s[0];
            }
            break;
        case 1:
            while (current != nullptr) {
                current->letter = word[j];
                j++;
                current = current->s[1];
            }
            break;
        case 2:
            while (current != nullptr) {
                current->letter = word[j];
                j++;
                current = current->s[2];
            }
            break;
        case 3:
            while (current != nullptr) {
                current->letter = word[j];
                j++;
                current = current->s[3];
            }
            break;
        case 4:
            while (current != nullptr) {
                current->letter = word[j];
                j++;
                current = current->s[4];
            }
            break;
        case 5:
            while (current != nullptr) {
                current->letter = word[j];
                j++;
                current = current->s[5];
            }
            break;
        }
    }
}

std::vector<Tile*> Game::getSharedTiles(Word wordA, Word wordB) {
    std::vector<Tile*> sharedTiles;
    for (unsigned int i = 0; i < wordA.tiles.size(); i++) {
        for (unsigned int j = 0; j < wordB.tiles.size(); j++) {
            if (wordA.tiles[i] == wordB.tiles[j]) {
                sharedTiles.push_back(wordB.tiles[j]);
            }
        }
    }
    return sharedTiles;
}

bool Game::isAWord(std::string str) {
    std::ifstream input;
    input.open("/Users/daniel/Projects/Linguahexa/Linguahexa/words.txt");
    std::string line;
    if (input.is_open()) {
        while (std::getline(input, line)) {
            if (str == line) {
                return true;
            }
        }
    } else {
      std::cout << "ERROR: Failed to open input file." << std::endl;
    }
    return false;
}

void Game::printBoard() {
    for (int i = 0; i < BOARD_MAX_HEIGHT; i++) {
        for (int j = 0; j < BOARD_MAX_WIDTH; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
