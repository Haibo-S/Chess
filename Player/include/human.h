#ifndef _HUMAN_H__
#define _HUMAN_H__

#include <vector>
#include "./player.h"

class Human: public Player {
  public:
    Human(Team tc, Board *b, Game *g, bool t) : Player(tc, b, g, t) {};
    void turn() override;
    void resign();
};

#endif
