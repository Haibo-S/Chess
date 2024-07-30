#include "./../include/pawn.h"

#include <algorithm> 


Pawn::Pawn(Team t, int row, int col)
    :  Piece{t, row, col}, allowEnPassant{false} {}

PieceType Pawn::getPieceType() {
    return PieceType::PAWN;
}

std::vector<std::vector<int>> Pawn::fetchAllMoves() {
    std::vector<int> curPos = getPosition();
    std::vector<std::vector<int>> allMoves;

    int direction = (getTeam() == Team::W) ? -1 : 1;

    if (curPos[0] + direction >= 0 && curPos[0] + direction < 8) {
        allMoves.push_back({curPos[0] + direction, curPos[1]});
    }

    if (!hasMoved) {
        if (curPos[0] + 2 * direction >= 0 && curPos[0] + 2 * direction < 8) {
            allMoves.push_back({curPos[0] + 2 * direction, curPos[1]});
        }
    }

    if(curPos[1] >= 1) {
        allMoves.push_back({curPos[0] + direction, curPos[1] - 1});
    }

    if(curPos[1] <= 6){
        allMoves.push_back({curPos[0] + direction, curPos[1] + 1});
    }


    return allMoves;
}

void Pawn::setEnPassant(bool b) {
    allowEnPassant = b;
}

bool Pawn::getEnPassant() {
    return allowEnPassant;
}

