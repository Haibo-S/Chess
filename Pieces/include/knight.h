#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "piece.h"

class Knight : public Piece {
public:
    Knight(Team t, int row, int col, std::vector<Piece*>& pieces);
    PieceType getPieceType() override;
    std::vector<std::vector<int>> fetchAllMoves() override;
    std::vector<std::vector<int>> fetchAllCaptureMoves() override;
    bool checkAttackOnEnemyKing() override;
};

#endif
