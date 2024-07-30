#include "./../include/knight.h"
#include <algorithm>  

Knight::Knight(Team t, int row, int col)
    : Piece(t, row, col) {}

PieceType Knight::getPieceType() {
    return PieceType::KNIGHT;
}

std::vector<std::vector<int>> Knight::fetchAllMoves() {
    std::vector<std::vector<int>> allMoves;
    std::vector<int> curPos = getPosition();

    // Possible moves for a knight
    std::vector<std::pair<int, int>> moves = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    for (const auto& move : moves) {
        int x = curPos[0] + move.first;
        int y = curPos[1] + move.second;

        if (x >= 0 && x < 8 && y >= 0 && y < 8) {
            allMoves.push_back({x, y});
        }
    }

    return allMoves;
}

// std::vector<std::vector<int>> Knight::fetchAllCaptureMoves() {
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

// bool Knight::checkAttackOnEnemyKing() {
//     std::vector<int> kingPos = locateEnemyKing();
//     std::vector<std::vector<int>> allMoves = fetchAllMoves();

//     return std::find(allMoves.begin(), allMoves.end(), kingPos) != allMoves.end();
// }

