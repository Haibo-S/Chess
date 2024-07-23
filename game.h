#ifndef __GAME_H__
#define __GAME_H__

#include "Board/include/board.h"
#include "Pieces/include/piece.h"
#include "Display/include/display.h"
#include <iostream>
#include <string>

class Game {

    Board board;
    Team cur;

    void switchTurn();
    bool isValidMove(int r1, int c1, int r2, int c2);
    bool isCheck(Team& team);
    bool isCheckmate(Team& team);
    bool isStalemate(Team &team);
    void moveCommand(const std::string &command);

    public:

        Game() : cur{Team::W}, board{new Text()} {};
        void start();
        void commandHandler(const std::string &command);
};

#endif