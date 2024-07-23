#ifndef __BOARD_H__
#define __BOARD_H__

#include "tile.h"
#include "./../../Display/include/observer.h"
#include <vector>

class Board {
  private:
    std::vector<std::vector<Tile>> tiles;
    Observer *display;

  public:
    Board(Observer *display) : display{display} {};
    ~Board();

    void initialize();
    Tile& getTile(int row, int col);
    bool movePiece(int startRow, int startCol, int endRow, int endCol);
    bool isCheck(Team team);
    bool isCheckmate(Team team);
    bool isStalemate(Team team);
    void setDisplay(Observer *display);
    void update(const Tile& tile);
};

#endif 
