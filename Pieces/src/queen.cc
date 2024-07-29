#include "./../include/queen.h"
#include <algorithm>  

// Queen::Queen(Team t, int row, int col, std::vector<Piece*>& pieces)
    // : Piece(t, row, col, pieces) {}

Queen::Queen(Team t, int row, int col)
    : Piece(t, row, col) {}

PieceType Queen::getPieceType() {
    return PieceType::QUEEN;
}

std::vector<std::vector<int>> Queen::fetchAllMoves() {
    std::vector<std::vector<int>> allMoves;
    std::vector<int> curPos = getPosition();

    std::vector<std::pair<int, int>> directions = {
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1},  // Diagonal
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}     // Horizontal and vertical
    };


    for (const auto& dir : directions) {
        int x = curPos[0] + dir.first;
        int y = curPos[1] + dir.second;

        while (x >= 0 && x < 8 && y >= 0 && y < 8) {
            allMoves.push_back({x, y});
            x += dir.first;
            y += dir.second;
        }
    }

    return allMoves;
}

// std::vector<std::vector<int>> Queen::fetchAllCaptureMoves() {
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

// bool Queen::checkAttackOnEnemyKing() {
//     std::vector<int> kingPos = locateEnemyKing();
//     std::vector<std::vector<int>> allMoves = fetchAllMoves();

//     return std::find(allMoves.begin(), allMoves.end(), kingPos) != allMoves.end();
// }

// bool Queen::onPath(const std::vector<int>& pos) {
//     for (const auto& piece : pieces) {
//         if (piece->getPosition() == pos) {
//             return true;
//         }
//     }
//     return false;
// }
