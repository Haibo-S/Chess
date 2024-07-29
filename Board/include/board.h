#ifndef __BOARD_H__
#define __BOARD_H__

#include "subject.h"
#include "./../../Board/include/tile.h"
#include "./../../Display/include/text.h"
#include "./../../Display/include/graphic.h"
#include "./../../Pieces/include/piece.h"
#include "./../../Pieces/include/bishop.h"
#include "./../../Pieces/include/rook.h"
#include "./../../Pieces/include/queen.h"
#include "./../../Pieces/include/king.h"
#include "./../../Pieces/include/pawn.h"
#include "./../../Pieces/include/knight.h"
#include <vector>

using namespace std;

class Board {
  private:
    std::vector<std::vector<Tile>> board;
    Team turn; // white or black
    Text td;
    Graphic gd;

  public:
    Board(int windowSize) : td{}, gd{windowSize} {};
    ~Board(){this->board.clear();};
    Tile& getTile(int r, int c);
    void init();
    void initDefault();
    bool move(vector<int> from, vector<int> to);
    // bool moveForComputer(vector<int> start, vector<int> end);
    // bool isCheck();
    // bool isCheckmate();
    // bool isStalemate();
    void toggleTurn();
    // Colour getCheckedPlayer();
    friend ostream &operator<<(ostream &out, const Board &b);
    // void resign();
    bool removePiece(vector<int> coord);
    void placeBoardPiece(int r, int c, char p, bool team);
    // void setPiece(int row, int col, Piece *p);
    // void detachPiece(int row, int col);
    // void deletePiece(int row, int col);
    // Piece *getPiece(int row, int col);
    vector<Piece*> getAllWhitePieces();
    vector<Piece*> getAllBlackPieces();
    vector<Piece*> getAllKingPieces();
    vector<Piece*> getAllPieces();
    // bool promote(int row, int col , char type);
};

#endif 
