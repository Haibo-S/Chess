#include "./../include/pawn.h"

#include <algorithm> 

// Pawn::Pawn(Team t, int row, int col, std::vector<Piece*>& pieces)
//     : Piece{t, row, col, pieces}, doubleMove{true}, allowEnPassant{false} {}

Pawn::Pawn(Team t, int row, int col)
    :  Piece{t, row, col}, allowEnPassant{false} {}

PieceType Pawn::getPieceType() {
    return PieceType::PAWN;
}

std::vector<std::vector<int>> Pawn::fetchAllMoves() {
    std::vector<int> curPos = getPosition();
    std::vector<std::vector<int>> allMoves;

    int direction = (getTeam() == Team::W) ? 1 : -1;

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

    // for (auto piece : pieces) {
        // std::vector<int> piecePos = this->getPosition();

        // if (piecePos[1] == curPos[1]) {
        //     if (piecePos[0] == curPos[0] + direction) {
        //         allMoves.erase(std::remove(allMoves.begin(), allMoves.end(), std::vector<int>{curPos[0] + direction, curPos[1]}), allMoves.end());
        //         if (doubleMove) {
        //             allMoves.erase(std::remove(allMoves.begin(), allMoves.end(), std::vector<int>{curPos[0] + 2 * direction, curPos[1]}), allMoves.end());
        //         }
        //     }
        // }

        // if ((piecePos == std::vector<int>{curPos[0] + direction, curPos[1] - 1} || piecePos == std::vector<int>{curPos[0] + direction, curPos[1] + 1}) && this->getTeam() != getTeam()) {
        //     allMoves.push_back(piecePos);
        // }
    // }

    return allMoves;
}

// std::vector<std::vector<int>> Pawn::fetchAllCheckMoves() {
//     std::vector<int> curPos = getPosition();
//     std::vector<std::vector<int>> allMoves = fetchAllMoves();
//     std::vector<std::vector<int>> checkMoves;

//     for (const auto& move : allMoves) {
//         this->move(move[0], move[1]);
//         if (checkAttackOnEnemyKing()) {
//             checkMoves.push_back(move);
//         }
//     }

//     this->move(curPos[0], curPos[1]);
//     return checkMoves;
// }

// std::vector<std::vector<int>> Pawn::fetchAllCaptureMoves() {
//     std::vector<int> curPos = getPosition();
//     std::vector<std::vector<int>> captureMoves;

//     for (auto piece : pieces) {
//         if (piece->getTeam() != getTeam()) {
//             std::vector<int> piecePos = piece->getPosition();
//             int direction = (getTeam() == Team::W) ? 1 : -1;

//             if (piecePos == std::vector<int>{curPos[0] + direction, curPos[1] - 1} || piecePos == std::vector<int>{curPos[0] + direction, curPos[1] + 1}) {
//                 captureMoves.push_back(piecePos);
//             }
//         }
//     }

//     return captureMoves;
// }

// bool Pawn::checkAttackOnEnemyKing() {
//     std::vector<int> curPos = getPosition();
//     std::vector<int> kingPos = locateEnemyKing();
//     int direction = (getTeam() == Team::W) ? 1 : -1;

//     return kingPos == std::vector<int>{curPos[0] + direction, curPos[1] - 1} || kingPos == std::vector<int>{curPos[0] + direction, curPos[1] + 1};
// }

// void Pawn::setDoubleMoveFalse() {
//     doubleMove = false;
// }

void Pawn::setEnPassant(bool b) {
    allowEnPassant = b;
}

bool Pawn::getEnPassant() {
    return allowEnPassant;
}

