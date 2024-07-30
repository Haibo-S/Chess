#ifndef _LEVEL4_H__
#define _LEVEL4_H__

#include <vector>
#include "./player.h"
#include "./../../game.h"

class Level4: public Player {
  public:
    Level4(Team tc, Board *b, Game *g, bool t) : Player(tc, b, g, t){};
    void turn() override;
};

#endif
