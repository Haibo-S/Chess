#include "./../include/piece.h"

#include <algorithm> 

Piece::~Piece() {}

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

// void Piece::setAllPieces(std::vector<Piece*>& p){
//     this->pieces = p;
// }

// void Piece::removePiece(Piece* p){
//     this->pieces.erase(std::remove(this->pieces.begin(), this->pieces.end(), p), this->pieces.end());
// }

// void Piece::addPiece(Piece* p) {
//     this->pieces.push_back(p);
// }

// std::vector<Piece*>& Piece::getAllPieces(){
//     return this->pieces;
// }

PieceType Piece::getPieceType(){
    return PieceType::NONE;
}

bool Piece::getHasMoved(){
    return hasMoved;
}

void Piece::setHasMovedToTrue(){
    hasMoved = true;
}

// bool Piece::checkAttackOnEnemyKing() {
//     auto positionEnemyKing = locateEnemyKing();
//     auto allMoves = fetchAllMoves();

//     return std::find(allMoves.begin(), allMoves.end(), positionEnemyKing) != allMoves.end();
// }

// std::vector<int> Piece::locateEnemyKing() {
//     // for (auto piece : this->pieces) {
//         if (this->getPieceType() == PieceType::KING && this->getTeam() != getTeam()) {
//             return this->getPosition();
//         }
//     // }
//     return std::vector<int>{-1, -1};
// }

// std::vector<std::vector<int>> Piece::fetchAllCheckMoves() {
//     std::vector<int> curPos = getPosition();
//     std::vector<std::vector<int>> allMoves = fetchAllMoves();
//     std::vector<std::vector<int>> checkMoves;

//     for (const auto& move : allMoves) {
//         this->move(move[0], move[1]);
//         // if (checkAttackOnEnemyKing()) {
//         //     checkMoves.push_back(move);
//         // }
//     }

//     this->move(curPos[0], curPos[1]);
//     return checkMoves;
// }

// bool Piece::verifyIfChecked() {
//     return false;
// }

