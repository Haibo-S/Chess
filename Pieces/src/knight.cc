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
