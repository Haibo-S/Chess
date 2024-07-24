#ifndef _LEVEL3_H__
#define _LEVEL3_H__

#include <vector>
#include "./player.h"

class Level3: public Player {
  public:
    Level3(Team tc, Board *b, bool t);
    void turn() override;
};

#endif
