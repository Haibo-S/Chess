#ifndef __GAME_H__
#define __GAME_H__

#include "Board/include/board.h"
#include "Pieces/include/piece.h"
#include "Display/include/text.h"
#include "Display/include/graphic.h"
#include <iostream>
#include <string>

extern bool isEnpassantMove;

class Game {

    Board board;
    Team cur;
    vector<vector<int>> prevMove;

    void switchTurn();
    bool isValidMove(int r1, int c1, int r2, int c2);
    bool isCheck();
    bool isCheckmate();
    bool isStalemate();
    void moveCommand(const std::string &command);
    bool checkCheck(int r1, int c1, int r2, int c2);
    bool isPathObstructed(int r1, int c1, int r2, int c2);
    
    public:

        Game() : cur{Team::W}, board{500} {
            board.init();
            board.initDefault();
        };
        void start();
        void commandHandler(const std::string &command);
};

#endif