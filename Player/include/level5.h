#ifndef _LEVEL5_H__
#define _LEVEL5_H__

#include <vector>
#include <map>
#include "./player.h"
#include "./../../game.h"

class Level5: public Player {

  public:
    Level5(Team tc, Board *b, Game *g, bool t) : Player(tc, b, g, t){
    std::srand(std::time(0));

    };


    int getVal(PieceType type);
        bool isCapturable(int row, int col);
    int evaluate(int r1, int c1, int r2, int c2);
    void turn() override;
};

#endif
