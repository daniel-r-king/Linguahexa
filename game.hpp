#include "constants.hpp"
#include "tile.hpp"
#include "word.hpp"
#include <string>
#include <vector>

class Game {
public:
    Game();
    ~Game();

    std::vector<std::vector<std::string>> board;

    std::vector<Word> wordSlots;

    std::vector<Tile> gameTiles;

    std::vector<std::vector<std::string>> backupBoard();

    void placeTile(std::string letter, int r, int c);

    void moveTile(int fr, int fc, int tr, int tc);

    void removeTile(int r, int c);

    bool boardIsEmpty();

    bool placeContiguousTiles(int x, int y, int length, int direction);

    bool outOfBounds(int r, int c, int length, int direction);

    bool validateCoordinates(int r, int c);

    void placeTiles();

    void linkTiles();

    void clear();

    void arrangeBoard();

    void constructWordSlots();

    void trimWordSlots();

    std::string getRandomWord(int length);

    void placeWordsAtRandom();

    bool puzzleIsCoherent();

    void placeWordsContingently();

    void getWords(unsigned int length, char letter, int index, std::vector<std::string>* words);

    bool isAWord(std::string str);

    std::vector<Tile*> getSharedTiles(Word a, Word b);

    int getTileIndex(Word word, Tile* tile, int direction);

    void invertWord(Word* word);

    void printMenu();

    std::string getLetter();

    int getRow();

    int getColumn();

    void printBoard();
};
