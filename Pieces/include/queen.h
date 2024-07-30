#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "piece.h"

class Queen : public Piece {
public:
  Queen(Team t, int row, int col);
  PieceType getPieceType() override;
  std::vector<std::vector<int>> fetchAllMoves() override;

};

#endif

