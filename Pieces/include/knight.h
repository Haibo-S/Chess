#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "piece.h"

class Knight : public Piece {
public:
    Knight(Team t, int row, int col);
    ~Knight() override;
    
    PieceType getPieceType() override;
    std::vector<std::vector<int>> fetchAllMoves() override;
};

#endif
