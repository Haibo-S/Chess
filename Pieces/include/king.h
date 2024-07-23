#ifndef __KING_H__
#define __KING_H__

#include "piece.h"

class King : public Piece {
  public:
    King(Team team, int row, int col) : Piece(team, row, col) {};
    void move() override;
    PieceType getPieceType() override;
    std::vector<std::vector<int>> canMoveTo() override;
    std::vector<std::vector<int>> canCapture() override;
    std::vector<std::vector<int>> canCheck() override;
};

#endif
