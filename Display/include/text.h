#ifndef __TEXT_H__
#define __TEXT_H__

#include <iostream>
#include <vector>
#include "observer.h"
#include "./../../Board/include/tile.h"

#define boardSize = 8;

class Text: public Observer {
    std::vector<std::vector<char>> boardDisplay;
    const int gridSize = 8;

    public:
        Text();
        void notify(Tile &tile) override;
        friend std::ostream &operator<<(std::ostream &out, const Text &text);
        

        char printChar(Tile& tile);
};

#endif
