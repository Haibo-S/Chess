#include "../include/tile.h"

void Tile::placePiece(Piece *piece){
    this->removePiece();
    p = piece;
    notifyObservers(*this);
}

void Tile::removePiece(){
    Piece* oldP = p;
    if(oldP) delete p;
    p = nullptr;
}

Piece* Tile::getPiece(){
    return this->p;
}

PieceType Tile::getPieceType(){
    return this->p->getPieceType();
}

int Tile::getRow(){
    return this->row;
}

int Tile::getCol(){
    return this->col;
}

Colour Tile::getColour(){
    return this->colour;
}

void Tile::setColour(Colour c){
    this->colour = c;
}

void Tile::promotion(PieceType type){
    // implement this shit later
}


