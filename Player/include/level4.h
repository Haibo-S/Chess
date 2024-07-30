#ifndef _LEVEL4_H__
#define _LEVEL4_H__

#include <vector>
#include <map>
#include "./player.h"
#include "./../../game.h"

class Level4: public Player {

  public:
    Level4(Team tc, Board *b, Game *g, bool t) : Player(tc, b, g, t){
    std::srand(std::time(0));

    };


    int getVal(PieceType type);
        bool isCapturable(std::vector<std::vector<char>>board2, int row, int col);

    void turn() override;
};

#endif
