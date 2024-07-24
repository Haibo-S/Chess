#ifndef __BOARD_H__
#define __BOARD_H__

#include "./../../Board/include/tile.h"
#include "./../../Display/include/text.h"
#include "./../../Display/include/graphic.h"
#include <vector>

class Board {
  private:
    std::vector<std::vector<Tile>> board;
    Team turn; // white or black
    Observer *display;
    Text* td;
    Graphic* gd;

  public:
    Board(Observer *display) : display{display} {};
    ~Board();

    void initialize();
    Tile& getTile(int row, int col);
    bool movePiece(int startRow, int startCol, int endRow, int endCol);
    bool isCheck();
    bool isCheckmate();
    bool isStalemate();
    void setDisplay(Observer *display);
    void update(const Tile& tile);
};

#endif 
