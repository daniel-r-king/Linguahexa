#include <vector>
#include <string>

#ifndef TILE_H
#define TILE_H

class Tile {
public:
    Tile();
    Tile(std::string letter);
    Tile(std::string letter, int r, int c);

    ~Tile();

    std::string letter;
    std::vector<Tile*> s;
    int r;
    int c;

    int getNumberOfEmptySides(Tile* tile);
    void printSides();
    void printAll();

    bool matches(Tile* tile);
};

#endif // TILE_H
