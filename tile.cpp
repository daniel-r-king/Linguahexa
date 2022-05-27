#include "tile.hpp"
#include "game.hpp"
#include <iostream>
Tile::Tile() {
    letter = " ";
    r = -1;
    c = -1;
    s = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
    // sides = { new Tile(" "), new Tile(" "), new Tile(" "), new Tile(" "), new Tile(" "), new Tile(" ") };
}

Tile::Tile(std::string letter) {
    this->letter = letter;
    r = -1;
    c = -1;
    s = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
}

Tile::Tile(std::string letter, int r, int c) {
    this->letter = letter;
    this->r = r;
    this->c = c;
    s = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
}

Tile::~Tile() {
}

int Tile::getNumberOfEmptySides(Tile *tile) {
    int nEmptySides = 0;
    for (int i = 0; i < N_SIDES_ON_TILE; i++) {
        if (tile->s[i] == nullptr) {
            nEmptySides++;
        }
    }
    return nEmptySides;
}

void Tile::printSides() {
    for (int i = 0; i < N_SIDES_ON_TILE; i++) {
        std::cout << s[i]->letter;
    }
    std::cout << std::endl;
}

void Tile::printAll() {
    std::cout << this << " (" << r << ", " << c << ")" << std::endl;
    std::cout << "letter = " << letter << std::endl;
    for (int i = 0; i < N_SIDES_ON_TILE; i++) {
        if (s[i]) {
            std::cout << "s" << i << " = " << s[i] << " ";
        } else {
            std::cout << "s" << i << " = " << "* ";
        }
    }
    std::cout << std::endl;
}

bool Tile::matches(Tile* tile) {
    if (tile->s[0] == this->s[0]
            && tile->s[1] == this->s[1]
            && tile->s[2] == this->s[2]
            && tile->s[3] == this->s[3]
            && tile->s[4] == this->s[4]
            && tile->s[5] == this->s[5]) {
        return true;
    } else {
        return false;
    }
}
