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
        if (i % 2 == 0) {
            for (int j = 0; j < BOARD_MAX_WIDTH; j++) {
                if (j % 2 != 0) {
                    strings.push_back(BUILDABLE_SPACE);
                } else {
                    strings.push_back(BLOCKED_SPACE);
                }
            }
        } else {
            for (int j = 0; j < BOARD_MAX_WIDTH; j++) {
                if (j % 2 == 0) {
                    strings.push_back(BUILDABLE_SPACE);
                } else {
                    strings.push_back(BLOCKED_SPACE);
                }
            }
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

void Game::placeTile(std::string letter, int r, int c) {
    if (validateCoordinates(r, c) && !outOfBounds(r, c, 1, 0)) {
        std::string str = "[" + letter + "]";
        board[r][c] = str;
        Tile tile(letter, r, c);
        gameTiles.push_back(tile);
    }
    else {
        std::cout << "ERROR: Selected coordinates invalid or out of bounds" << std::endl;
    }
}

void Game::moveTile(int fr, int fc, int tr, int tc) {
    for (unsigned int i = 0; i < gameTiles.size(); i++) {
        if (gameTiles[i].r == fr && gameTiles[i].c == fc) {
            gameTiles[i].r = tr;
            gameTiles[i].c = tc;
            board[fr][fc] = BUILDABLE_SPACE;
            board[tr][tc] = "[" + gameTiles[i].letter + "]";
        }
    }
}

void Game::removeTile(int r, int c) {
    board[r][c] = BUILDABLE_SPACE;
    for (unsigned int i = 0; i < gameTiles.size(); i++) {
        if (gameTiles[i].r == r && gameTiles[i].c == c) {
            gameTiles.erase(gameTiles.begin() + i);
        }
    }
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

bool Game::outOfBounds(int r, int c, int length, int direction) {
    switch (direction) {
    case 0:
        if (r % 2 != 0 && r + 1 - (length * 2) < 0) {
            std::cout << "game.cpp::163" << std::endl;
            return true;
        }
        if (r % 2 == 0 && r + 2 - (length * 2) < 0) {
            std::cout << "game.cpp::167" << std::endl;
            return true;
        }
        break;
    case 1:
        if (length > r + 1) {
            std::cout << "game.cpp::173" << std::endl;
            return true;
        }
        break;
    case 2:
        if (length > (-1 * r) + BOARD_MAX_HEIGHT) {
            std::cout << "game.cpp::179" << std::endl;
            return true;
        }
        break;
    case 3:
        if (r % 2 != 0 && length > (BOARD_MAX_HEIGHT - r) / 2) {
            std::cout << "game.cpp::185" << std::endl;
            return true;
        }
        if (r % 2 == 0 && length > ((BOARD_MAX_HEIGHT - r) + 1) / 2) {
            std::cout << "game.cpp::189" << std::endl;
            return true;
        }
        break;
    case 4:
        if (length > c + 1) {
            std::cout << "game.cpp::195" << std::endl;
            return true;
        }
        break;
    case 5:
        // r = 0, max l = 1 for all c
        // r = 2, max l = 3 for all c > 1, else max l = c + 1
        // r = 4, max l = 5 for all c > 3, else max l = c + 1
        // r = 6, max l = 7 for all c > 5, else max l = c + 1
        // r = 8, max l = 9 for all c > 7, else max l = c + 1
        // r = 10,max l = 11for all c > 9, else max l = c + 1
        // r = 12,max l = 13for all c > 11,else max l = c + 1
        // r = 14,max l = 14for all c > 11,else max l = c + 1

        // r = 1, max l = 2 for all c > 0, else max l = c + 1
        // r = 3, max l = 4 for all c > 2, else max l = c + 1
        // r = 5, max l = 6 for all c > 4, else max l = c + 1
        // r = 7, max l = 8 for all c > 6, else max l = c + 1
        // r = 9, max l = 10for all c > 8, else max l = c + 1
        // r = 11,max l = 12for all c > 10,else max l = c + 1
        // r = 13,max l = 14for all c > 12,else max l = c + 1
        int maxLength = 0;
        if (r == BOARD_MAX_HEIGHT - 1) {
            maxLength = BOARD_MAX_HEIGHT - 1;
        }
        else {
            if (c > r - 1) {
                maxLength = r + 1;
            }
            else {
                maxLength = c + 1;
            }
        }
        if (length > maxLength) {
            std::cout << "game.cpp::229" << std::endl;
            return true;
        }
        break;
    }
    return false;
}

bool Game::validateCoordinates(int r, int c) {
    if ((r % 2 == 0 && c % 2 != 0) || (r % 2 != 0 && c % 2 == 0)) {
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
    input.open("words.txt");
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
    input.open("words.txt");
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
            std::cout << forward << std::endl;
            std::cout << backward << std::endl;
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

void Game::placeWordsContingently() {
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
    input.open("words.txt");
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

void Game::printMenu() {
    std::cout << "1. Place a tile" << std::endl;
    std::cout << "2. Move a tile" << std::endl;
    std::cout << "3. Delete a tile" << std::endl;
    std::cout << "4. Check puzzle coherence" << std::endl;
    std::cout << "5. Finish" << std::endl;
    std::cout << "Enter an option <1-5>: ";
}

std::string Game::getLetter() {
    std::string str;
    std::cout << "Enter a letter: ";
    std::cin >> str;
    return str;
}

int Game::getRow() {
    int r;
    std::cout << "Enter a row: ";
    std::cin >> r;
    return r;
}

int Game::getColumn() {
    int c;
    std::cout << "Enter a column: ";
    std::cin >> c;
    return c;
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
