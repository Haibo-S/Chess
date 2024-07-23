#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "piece.h"

class Knight : public Piece {
  public:
    Knight(Team team, int row, int col) : Piece(team, row, col) {};
    void move() override;
    PieceType getPieceType() override;
    std::vector<std::vector<int>> canMoveTo() override;
    std::vector<std::vector<int>> canCapture() override;
    std::vector<std::vector<int>> canCheck() override;
};

#endif
