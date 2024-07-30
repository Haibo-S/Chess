#ifndef __PAWN_H__
#define __PAWN_H__

#include "piece.h"

class Pawn : public Piece {
  bool allowEnPassant = false;
public:
  Pawn(Team t, int row, int col);
  PieceType getPieceType() override;
  std::vector<std::vector<int>> fetchAllMoves() override;

  void setEnPassant(bool b);
  bool getEnPassant();
};

#endif

