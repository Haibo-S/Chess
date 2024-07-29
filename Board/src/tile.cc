#include "../include/tile.h"

void Tile::placePiece(Piece *piece){
    if(getPiece() != nullptr) this->removePiece();
    p = piece;
    notifyObservers(*this);
}

void Tile::removePiece(){

    if(p) {
        p = nullptr;
        notifyObservers(*this);
    }

}



void Tile::checkPlace(Piece *piece){
    if(getPiece() != nullptr) this->checkRemove();
    p = piece;
}

void Tile::checkRemove(){

    if(p) {
        p = nullptr;
    }

}
Piece* Tile::getPiece(){
    return this->p;
}

PieceType Tile::getPieceType(){
    if(getPiece() == nullptr){
        return PieceType::NONE;
    }
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


