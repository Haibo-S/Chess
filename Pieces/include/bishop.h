#ifndef __BISHOP_H__
#define __BISHOP_H__

#include "piece.h"

class Bishop : public Piece {
public:
  
  Bishop(Team t, int row, int col);
  PieceType getPieceType() override;
  std::vector<std::vector<int>> fetchAllMoves() override;
};

#endif

