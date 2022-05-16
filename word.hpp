#ifndef WORD_H
#define WORD_H
#include "tile.hpp"


class Word {
public:
    Word();
    ~Word();
    Tile* start;
    Tile* end;
    std::vector<Tile*> tiles;
    std::string word;
    int length;
    int direction;
};

#endif // WORD_H
