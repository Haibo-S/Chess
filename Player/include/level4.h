#ifndef _LEVEL4_H__
#define _LEVEL4_H__

#include <vector>
#include "./player.h"

class Level4: public Player {
  public:
    Level4(Team tc, Board *b, bool t);
    void turn() override;
};

#endif
