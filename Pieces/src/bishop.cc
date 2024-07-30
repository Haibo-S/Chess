#include "./../include/bishop.h"
#include <algorithm>  

// Bishop::Bishop(Team t, int row, int col, std::vector<Piece*>& pieces)
//     : Piece(t, row, col, pieces) {}

Bishop::Bishop(Team t, int row, int col)
    : Piece(t, row, col) {}

PieceType Bishop::getPieceType() {
    return PieceType::BISHOP;
}

std::vector<std::vector<int>> Bishop::fetchAllMoves() {
    std::vector<std::vector<int>> allMoves;
    std::vector<int> directions = {-1, 1};
    std::vector<int> curPos = getPosition();

    for (int dx : directions) {
        for (int dy : directions) {
            int x = curPos[0] + dx;
            int y = curPos[1] + dy;

            while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                allMoves.push_back({x, y});
                // if (onPath({x, y})) break;
                x += dx;
                y += dy;
            }
        }
    }

    return allMoves;
}

// std::vector<std::vector<int>> Bishop::fetchAllCaptureMoves() {
//     std::vector<std::vector<int>> captureMoves;
//     std::vector<std::vector<int>> allMoves = fetchAllMoves();

//     for (const auto& move : allMoves) {
//         for (const auto& piece : pieces) {
//             if (piece->getPosition() == move && piece->getTeam() != getTeam()) {
//                 captureMoves.push_back(move);
//             }
//         }
//     }

//     return captureMoves;
// }

// bool Bishop::checkAttackOnEnemyKing() {
//     std::vector<int> kingPos = locateEnemyKing();
//     std::vector<std::vector<int>> allMoves = fetchAllMoves();

//     return std::find(allMoves.begin(), allMoves.end(), kingPos) != allMoves.end();
// }

// bool Bishop::onPath(const std::vector<int>& pos) {
//     for (auto piece : pieces) {
//         if (piece->getPosition() == pos) {
//             return true;
//         }
//     }
//     return false;
// }


