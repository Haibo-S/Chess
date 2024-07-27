#include "./../include/king.h"
#include <algorithm>  // For std::find

// King::King(Team t, int row, int col, std::vector<Piece*>& pieces)
//     : Piece(t, row, col, pieces) {}

King::King(Team t, int row, int col)
    : Piece(t, row, col) {}

PieceType King::getPieceType() {
    return PieceType::KING;
}

std::vector<std::vector<int>> King::fetchAllMoves() {
    std::vector<std::vector<int>> allMoves;
    std::vector<int> curPos = getPosition();

    // Possible moves for a king
    std::vector<std::pair<int, int>> moves = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
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

// std::vector<std::vector<int>> King::fetchAllCheckMoves() {
//     // The king cannot check the enemy king, so return an empty vector
//     return std::vector<std::vector<int>>{};
// }

// std::vector<std::vector<int>> King::fetchAllCaptureMoves() {
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

// bool King::checkAttackOnEnemyKing() {
//     // The king cannot attack the enemy king directly in chess, so this should always return false
//     return false;
// }

// bool King::isBeingChecked() {
//     std::vector<int> kingPos = getPosition();
//     for (const auto& piece : pieces) {
//         if (piece->getTeam() != getTeam()) {
//             std::vector<std::vector<int>> enemyMoves = piece->fetchAllMoves();
//             if (std::find(enemyMoves.begin(), enemyMoves.end(), kingPos) != enemyMoves.end()) {
//                 return true;
//             }
//         }
//     }
//     return false;
// }

// bool King::getHasMoved(){
//     return this->hasMoved;
// }

// void King::setTrueForHasMoved(){
//     this->hasMoved = true;
// }

