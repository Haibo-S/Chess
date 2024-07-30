#ifndef __ROOK_H__
#define __ROOK_H__

#include "piece.h"

class Rook : public Piece {

public:

    Rook(Team t, int row, int col);

    PieceType getPieceType() override;
    std::vector<std::vector<int>> fetchAllMoves() override;

};

#endif
