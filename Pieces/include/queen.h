#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "piece.h"

class Queen : public Piece {
  public:
    Queen(Team team, int row, int col) : Piece(team, row, col) {};
    void move() override;
    PieceType getPieceType() override;
    std::vector<std::vector<int>> canMoveTo() override;
    std::vector<std::vector<int>> canCapture() override;
    std::vector<std::vector<int>> canCheck() override;
};

#endif
