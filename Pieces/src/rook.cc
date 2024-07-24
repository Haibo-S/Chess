#include "./../include/rook.h"
#include <algorithm>  // For std::find

Rook::Rook(Team t, int row, int col, std::vector<Piece*>& pieces)
    : Piece(t, row, col, pieces) {}

PieceType Rook::getPieceType() {
    return PieceType::ROOK;
}

std::vector<std::vector<int>> Rook::fetchAllMoves() {
    std::vector<std::vector<int>> allMoves;
    std::vector<int> curPos = getPosition();

    // Directions for horizontal and vertical moves
    std::vector<std::pair<int, int>> directions = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    for (const auto& dir : directions) {
        int x = curPos[0] + dir.first;
        int y = curPos[1] + dir.second;

        while (x >= 0 && x < 8 && y >= 0 && y < 8) {
            allMoves.push_back({x, y});
            if (onPath({x, y})) break;
            x += dir.first;
            y += dir.second;
        }
    }

    return allMoves;
}

std::vector<std::vector<int>> Rook::fetchAllCaptureMoves() {
    std::vector<std::vector<int>> captureMoves;
    std::vector<std::vector<int>> allMoves = fetchAllMoves();

    for (const auto& move : allMoves) {
        for (const auto& piece : pieces) {
            if (piece->getPosition() == move && piece->getTeam() != getTeam()) {
                captureMoves.push_back(move);
            }
        }
    }

    return captureMoves;
}

bool Rook::checkAttackOnEnemyKing() {
    std::vector<int> kingPos = locateEnemyKing();
    std::vector<std::vector<int>> allMoves = fetchAllMoves();

    return std::find(allMoves.begin(), allMoves.end(), kingPos) != allMoves.end();
}

bool Rook::onPath(const std::vector<int>& pos) {
    for (const auto& piece : pieces) {
        if (piece->getPosition() == pos) {
            return true;
        }
    }
    return false;
}


bool Rook::getHasMoved(){
    return this->hasMoved;
}

void Rook::setTrueForHasMoved(){
    this->hasMoved = true;
}

