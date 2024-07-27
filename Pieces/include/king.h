#ifndef __KING_H__
#define __KING_H__

#include "piece.h"

class King : public Piece {
    // bool hasMoved = false;
public:
    // King(Team t, int row, int col, std::vector<Piece*>& pieces);
    King(Team t, int row, int col);
    PieceType getPieceType() override;
    std::vector<std::vector<int>> fetchAllMoves() override;
    // std::vector<std::vector<int>> fetchAllCheckMoves() override;
    // std::vector<std::vector<int>> fetchAllCaptureMoves() override;
    // bool checkAttackOnEnemyKing() override;
    // bool isBeingChecked();

    // bool getHasMoved();
    // void setTrueForHasMoved();
};

#endif
