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
    // std::vector<Piece*> pieces;

  public:
    Piece(Team team, int row, int col): team{team}, row{row}, col{col}, hasMoved{false} {};
    // Piece(Team team, int row, int col, std::vector<Piece*>& pieces): team{team}, row{row}, col{col}, pieces{pieces} {};
    virtual ~Piece() = default;

    Team getTeam();
    void setTeam(Team color);
    std::vector<int> getPosition();
    void move(int r, int c);
    // void setAllPieces(std::vector<Piece*>& p);
    // void removePiece(Piece * p);
    // void addPiece(Piece *p);
    // std::vector<Piece*>& getAllPieces();


    virtual PieceType getPieceType() = 0;
    virtual std::vector<std::vector<int>> fetchAllMoves() = 0;

    virtual bool getInCheck();
    virtual void setInCheck();
    // virtual std::vector<std::vector<int>> fetchAllCheckMoves();
    // virtual std::vector<std::vector<int>> fetchAllCaptureMoves() = 0;
    // virtual bool checkAttackOnEnemyKing();
    // virtual std::vector<int> locateEnemyKing();
    // virtual bool verifyIfChecked();

    int getRow();
    int getCol();

    bool getHasMoved();
    void setHasMovedToTrue();

};

#endif 
