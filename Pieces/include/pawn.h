#ifndef __PAWN_H__
#define __PAWN_H__

#include "piece.h"

class Pawn : public Piece {
  // bool doubleMove = true;
  bool allowEnPassant = false;
public:
  Pawn(Team t, int row, int col);
  // Pawn(Team t, int row, int col, std::vector<Piece*>& pieces);
  PieceType getPieceType() override;
  std::vector<std::vector<int>> fetchAllMoves() override;
  ~Pawn() override;
  // std::vector<std::vector<int>> fetchAllCheckMoves() override;
  // std::vector<std::vector<int>> fetchAllCaptureMoves() override;
  // bool checkAttackOnEnemyKing() override;
  // void setDoubleMoveFalse();
  void setEnPassant(bool b);
  bool getEnPassant();
};

#endif

