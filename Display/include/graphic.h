#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <iostream>
#include <vector>
#include "observer.h"
#include "./../../Board/include/tile.h"
#include "./window.h"

class Graphic: public Observer {
    Xwindow w;
    const int windowSize;
    const int gridNum = 8;
    const int blockSize;
  public:
    Graphic(int windowSize);
    void notify(Tile &c) override;


    char drawChar(Tile& tile);
    void initializeGrid();
};

#endif