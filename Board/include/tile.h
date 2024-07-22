#ifndef __TILE_H__
#define __TILE_H__

#include <vector>
#include <iostream>
#include "observer.h"
#include "piece.h"

enum class Colour {B, W};

class Tile{

    Piece *p;
    int row,col;
    Colour colour; 

    public:
        Tile(int row, int col): row{row}, col{col}, p{nullptr}, colour{W} {};
        ~Tile();
        void placePiece(Piece *p);
        void removePiece();
        Piece* getPiece();
        int getRow();
        int getCol();
        Colour getColour();
        void promote();
};




#endif
