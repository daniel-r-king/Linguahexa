#include "constants.hpp"
#include "tile.hpp"
#include "word.hpp"
#include <string>
#include <vector>

#ifndef GAME_H
#define GAME_H

class Game {
public:
    Game();
    ~Game();

    std::vector<std::vector<std::string>> board;

    std::vector<Word> wordSlots;

    std::vector<Tile> gameTiles;

    std::vector<std::vector<std::string>> backupBoard();

    bool boardIsEmpty();

    bool placeContiguousTiles(int x, int y, int length, int direction);

    bool placeBaseTiles(int r, int c, int length, int direction);

    bool outOfBounds(int r, int c, int length, int direction);

    bool validateCoordinates(int r, int c);

    void placeTiles();

    void linkTiles();

    void clear();

    void arrangeBoard();

    int getDistance(Tile* tile, int direction);

    void constructWordSlots();

    void trimWordSlots();

    std::string getRandomWord(int length);

    void placeWordsAtRandom();

    bool puzzleIsCoherent();

    void placeWordByWord();

    void getWords(unsigned int length, char letter, int index, std::vector<std::string>* words);

    bool isAWord(std::string str);

    std::vector<Tile*> getSharedTiles(Word a, Word b);

    int getTileIndex(Word word, Tile* tile, int direction);

    void invertWord(Word* word);

    void printBoard();
};

#endif // GAME_H
