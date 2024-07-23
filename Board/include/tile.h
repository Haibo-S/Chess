#ifndef __TILE_H__
#define __TILE_H__

#include <vector>
#include <iostream>
#include "observer.h"
#include "piece.h"
#include "subject.h"

enum class Colour {B, W};

class Tile : public Subject{

    Piece *p;
    int row,col;
    Colour colour; 
    

    public:
        Tile(int row, int col): row{row}, col{col}, p{nullptr}, colour{Colour::W} {};
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
