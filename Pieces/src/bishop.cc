#include "./../include/bishop.h"
#include <algorithm>  

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
                x += dx;
                y += dy;
            }
        }
    }

    return allMoves;
}
