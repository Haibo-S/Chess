#ifndef __GAME_H__
#define __GAME_H__

#include "Board/include/board.h"
#include "Pieces/include/piece.h"
#include "Display/include/text.h"
#include "Display/include/graphic.h"
#include "Player/include/player.h"
#include "Player/include/human.h"
#include "Player/include/level1.h"
#include "Player/include/level2.h"
#include "Player/include/level3.h"
#include "Player/include/level4.h"
#include <iostream>
#include <string>

extern bool isEnpassantMove;
extern bool isCassleMove;

class Game {

    Board board;
    Team cur;
    Player* whitePlayer;
    Player* blackPlayer;
    Player* curPlayer;

    vector<vector<int>> prevMove;
    Tile* getKing();
    void switchTurn();
    bool isValidMove(int r1, int c1, int r2, int c2);
    bool checkValidMove(int r1, int c1, int r2, int c2);
    bool isCheck();

    bool isCheckmate();
    bool isStalemate();
    void moveCommand(const std::string &command);
    bool checkCheck();
    bool isPathObstructed(int r1, int c1, int r2, int c2);
    bool isKinginCheck();
    
    public:

        Game() : cur{Team::W}, board{500}, whitePlayer{new Human(Team::W, &board, true)}, blackPlayer{nullptr} {
            board.init();
            // board.initDefault();
        };
        ~Game();
        void start();
        void commandHandler(const std::string &command);
        bool setUpHandler(const std::string &command);
};

#endif