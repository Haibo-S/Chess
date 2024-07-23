#ifndef __PIECE_H__
#define __PIECE_H__
#include <vector>

enum class PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE };
enum class Team { W, B };

class Piece {

  protected:
    Team team;
    int row, col;

  public:
    Piece(Team team, int row, int col): team{team}, row{row}, col{col} {};
    virtual ~Piece() = default;

    virtual void move() = 0;
    virtual PieceType getPieceType() = 0;
    virtual std::vector<std::vector<int>> canMoveTo() = 0;
    virtual std::vector<std::vector<int>> canCapture() = 0;
    virtual std::vector<std::vector<int>> canCheck() = 0;

    Team getTeam();
    int getRow();
    int getCol();
    void setPosition(int newRow, int newCol);

};

#endif 
