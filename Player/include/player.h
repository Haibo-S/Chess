#ifndef _PLAYER_H__
#define _PLAYER_H__

#include <vector>
#include "./../../Board/include/board.h"

class Player {
protected:
    Team team;
    Board *board;
    bool turnActive;
public:
    Player(Team tc, Board *b, bool t);
    virtual ~Player();
    virtual void turn() = 0;
    bool getTurn();
    Team getTeam();
    void setTeam(Team tc);
    void setTurn(bool t);
};

#endif
