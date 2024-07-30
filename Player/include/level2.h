#ifndef _LEVEL2_H__
#define _LEVEL2_H__

#include <vector>
#include "./player.h"
#include "./../../game.h"

class Level2: public Player {
  public:
    Level2(Team tc, Board *b, Game *g, bool t) : Player(tc, b, g, t) {std::srand(std::time(0));};
    void turn() override;
};

#endif
