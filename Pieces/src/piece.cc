#include "./../include/piece.h"

#include <algorithm> 


Team Piece::getTeam() {
    return this->team;
}

void Piece::setTeam(Team color) {
    this->team = color;
}

std::vector<int> Piece::getPosition() {
    return std::vector<int>{this->row, this->col};
}

void Piece::move(int r, int c){
    this->row = r;
    this->col = c;
}


PieceType Piece::getPieceType(){
    return PieceType::NONE;
}

bool Piece::getHasMoved(){
    return hasMoved;
}

void Piece::setHasMovedToTrue(){
    hasMoved = true;
}
