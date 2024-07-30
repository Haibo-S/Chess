#include "./../include/rook.h"
#include <algorithm>

Rook::Rook(Team t, int row, int col)
    : Piece(t, row, col) {}

PieceType Rook::getPieceType()
{
    return PieceType::ROOK;
}

std::vector<std::vector<int>> Rook::fetchAllMoves()
{
    std::vector<std::vector<int>> allMoves;
    std::vector<int> curPos = getPosition();

    std::vector<std::pair<int, int>> directions = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (const auto &dir : directions)
    {
        int x = curPos[0] + dir.first;
        int y = curPos[1] + dir.second;

        while (x >= 0 && x < 8 && y >= 0 && y < 8)
        {
            allMoves.push_back({x, y});
            x += dir.first;
            y += dir.second;
        }
    }

    return allMoves;
}
