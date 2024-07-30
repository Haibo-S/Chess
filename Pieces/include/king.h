#ifndef __KING_H__
#define __KING_H__

#include "piece.h"

class King : public Piece {
    // bool hasMoved = false;
    bool inCheck;
public:
    // King(Team t, int row, int col, std::vector<Piece*>& pieces);
    
    King(Team t, int row, int col);
    PieceType getPieceType() override;
    ~King() override;
    std::vector<std::vector<int>> fetchAllMoves() override;
    // bool getInCheck() override;
    // void setInCheck() override;
    // std::vector<std::vector<int>> fetchAllCheckMoves() override;
    // std::vector<std::vector<int>> fetchAllCaptureMoves() override;
    // bool checkAttackOnEnemyKing() override;
    // bool isBeingChecked();

    // bool getHasMoved();
    // void setTrueForHasMoved();
};

#endif
