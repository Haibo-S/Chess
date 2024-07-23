#ifndef __TEXT_H__
#define __TEXT_H__

#include <iostream>
#include <vector>
#include "observer.h"

#define boardSize = 8;

class Text: public Observer {
    std::vector<std::vector<char>> boardDisplay;

    public:
        void notify(const Tile &tile) override;
        void drawBoard();

        friend std::ostream &operator<<(std::ostream &out, const Text &text);
};

#endif
