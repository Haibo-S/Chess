#ifndef _COMPUTER_H__
#define _COMPUTER_H__

#include <vector>
#include "player.h"

class Computer: public Player {
  public:
    virtual void turn() = 0;
};

#endif
