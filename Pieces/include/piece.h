#ifndef __PIECE_H__
#define __PIECE_H__
#include <vector>

enum class PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE };
enum class Team { W, B };

class Piece {

    Team team;
    int row, col;
    
    protected:
        std::vector<Piece*> pieces;
    public:
        virtual ~Piece() = default;
        virtual void move() = 0;
        virtual PieceType getPieceType() = 0;

        virtual std::vector<std::vector<int>> canMoveTo() = 0;
        virtual std::vector<std::vector<int>> canCapture() = 0;
        virtual std::vector<std::vector<int>> canCheck() = 0;
        

        Team getTeam();
};

#endif 
