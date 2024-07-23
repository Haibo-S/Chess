#ifndef __ROOK_H__
#define __ROOK_H__

#include "piece.h"

class Rook : public Piece {
  public:
    Rook(Team team, int row, int col) : Piece(team, row, col) {};
    void move() override;
    PieceType getPieceType() override;
    std::vector<std::vector<int>> canMoveTo() override;
    std::vector<std::vector<int>> canCapture() override;
    std::vector<std::vector<int>> canCheck() override;
};

#endif
