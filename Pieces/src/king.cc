#include "./../include/king.h"
#include <algorithm>  

King::King(Team t, int row, int col)
    : Piece(t, row, col) {}

PieceType King::getPieceType() {
    return PieceType::KING;
}

std::vector<std::vector<int>> King::fetchAllMoves() {
    std::vector<std::vector<int>> allMoves;
    std::vector<int> curPos = getPosition();

    std::vector<std::pair<int, int>> moves = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {0, 2}, {0, -2}
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
