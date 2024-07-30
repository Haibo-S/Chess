#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "piece.h"

class Queen : public Piece {
  // bool onPath(const std::vector<int>& pos);
public:
  // Queen(Team t, int row, int col, std::vector<Piece*>& pieces);
  Queen(Team t, int row, int col);
  PieceType getPieceType() override;
  std::vector<std::vector<int>> fetchAllMoves() override;
  // std::vector<std::vector<int>> fetchAllCaptureMoves() override;
  // bool checkAttackOnEnemyKing() override;
};

#endif

