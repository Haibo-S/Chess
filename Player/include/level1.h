#ifndef _LEVEL1_H__
#define _LEVEL1_H__

#include <vector>
#include "./player.h"
#include "./../../game.h"

class Level1: public Player {
  public:
    Level1(Team tc, Board *b, Game *g, bool t): Player(tc, b, g, t) {std::srand(std::time(0));};
    void turn() override;
};

#endif
