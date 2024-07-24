#ifndef __PAWN_H__
#define __PAWN_H__

#include "piece.h"

class Bishop : public Piece {
  bool onPath(const std::vector<int>& pos);
public:
  Bishop(Team t, int row, int col, std::vector<Piece*>& pieces);
  PieceType getPieceType() override;
  std::vector<std::vector<int>> fetchAllMoves() override;
  std::vector<std::vector<int>> fetchAllCaptureMoves() override;
  bool checkAttackOnEnemyKing() override;
};

#endif

