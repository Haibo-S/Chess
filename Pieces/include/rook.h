#ifndef __ROOK_H__
#define __ROOK_H__

#include "piece.h"

class Rook : public Piece {
    bool hasMoved = false;
    bool onPath(const std::vector<int>& pos);
public:
    Rook(Team t, int row, int col, std::vector<Piece*>& pieces);
    PieceType getPieceType() override;
    std::vector<std::vector<int>> fetchAllMoves() override;
    std::vector<std::vector<int>> fetchAllCaptureMoves() override;
    bool checkAttackOnEnemyKing() override;
};

#endif
