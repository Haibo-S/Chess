#ifndef _LEVEL3_H__
#define _LEVEL3_H__

#include <vector>
#include "./player.h"
#include "./../../game.h"

class Level3: public Player {
  public:
    Level3(Team tc, Board *b, Game *g, bool t) : Player(tc, b, g, t) {};
    bool isCapturable(int row, int col);
    void turn() override;
};

#endif
