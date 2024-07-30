#ifndef __KING_H__
#define __KING_H__

#include "piece.h"

class King : public Piece {
public:
    King(Team t, int row, int col);
    PieceType getPieceType() override;
    std::vector<std::vector<int>> fetchAllMoves() override;

};

#endif
