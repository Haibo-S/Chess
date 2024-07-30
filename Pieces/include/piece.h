#ifndef __PIECE_H__
#define __PIECE_H__
#include <iostream>
#include <vector>

enum class PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE };
enum class Team { W, B };

class Piece {

  protected:
    Team team;
    int row, col;
    bool hasMoved;

  public:
    Piece(Team team, int row, int col): team{team}, row{row}, col{col}, hasMoved{false} {};
    virtual ~Piece() = default;

    Team getTeam();
    void setTeam(Team color);
    std::vector<int> getPosition();
    void move(int r, int c);



    virtual PieceType getPieceType() = 0;
    virtual std::vector<std::vector<int>> fetchAllMoves() = 0;

    int getRow();
    int getCol();

    bool getHasMoved();
    void setHasMovedToTrue();

};

#endif 
