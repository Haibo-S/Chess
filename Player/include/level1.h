#ifndef _LEVEL1_H__
#define _LEVEL1_H__

#include <vector>
#include "./player.h"

class Level1: public Player {
  public:
    Level1(Team tc, Board *b, bool t);
    void turn() override;
};

#endif