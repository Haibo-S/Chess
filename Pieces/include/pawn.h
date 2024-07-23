#ifndef __PAWN_H__
#define __PAWN_H__

#include "piece.h"

class Pawn : public Piece {
  public:
    Pawn(Team team, int row, int col) : Piece(team, row, col) {};
    void move() override;
    PieceType getPieceType() override;
    std::vector<std::vector<int>> canMoveTo() override;
    std::vector<std::vector<int>> canCapture() override;
    std::vector<std::vector<int>> canCheck() override;
};

#endif
