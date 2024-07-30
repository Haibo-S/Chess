#ifndef _HUMAN_H__
#define _HUMAN_H__

#include <vector>
#include "./player.h"

class Human: public Player {
  public:
    Human(Team tc, Board *b, bool t);
    void turn() override;
    void resign();
};

#endif