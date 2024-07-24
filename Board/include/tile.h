#ifndef __TILE_H__
#define __TILE_H__

#include <vector>
#include <iostream>

#include "./../../Pieces/include/piece.h"
#include "./../../Display/include/observer.h"
#include "./subject.h"



enum class Colour {B, W};

class Tile : public Subject{

    Piece *p;
    int row,col;
    Colour colour;    

    public:
        Tile(int row, int col): row{row}, col{col}, p{nullptr}, colour{Colour::W} {};
        ~Tile() {
            if (p) delete p;
        }
        void placePiece(Piece *p);
        void removePiece();
        Piece* getPiece();
        PieceType getPieceType();
        int getRow ();
        int getCol();
        Colour getColour();
        void promotion();
};




#endif
