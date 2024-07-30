#ifndef __GAME_H__
#define __GAME_H__

#include "Board/include/board.h"
#include "Pieces/include/piece.h"
#include "Display/include/text.h"
#include "Display/include/graphic.h"
#include <iostream>
#include <string>

extern bool isEnpassantMove;
extern bool isCassleMove;

class Game {

    Board board;
    Team cur;
    vector<vector<int>> prevMove;
    vector<vector<char>> textdisplay;

    void switchTurn();

    bool isValidMove(int r1, int c1, int r2, int c2);
    bool simpleIsValidMove(int r1, int c1, int r2, int c2);

    bool isCheck();
    void moveCommand(const std::string &command);
    bool isPathObstructed(int r1, int c1, int r2, int c2);

    vector<vector<char>> printTable();
    bool isKingInCheck(const vector<vector<char>>& board, bool isWhite);
    bool isValid(int x, int y);
    bool isAttackedByPawn(const vector<vector<char>>& board, int x, int y, bool isWhite);
    bool isAttackedByKnight(const vector<vector<char>>& board, int x, int y, bool isWhite);
    bool isAttackedBySlidingPiece(const vector<vector<char>>& board, int x, int y, bool isWhite, const vector<pair<int, int>>& directions, char piece1, char piece2);

    vector<vector<int>> resolveCheckMoves();
    vector<vector<int>> allPossibleMoves();

    public:

        Game() : cur{Team::W}, board{500} {
            board.init();
            // board.initDefault();
        };
        void start();
        void commandHandler(const std::string &command);
        bool setUpHandler(const std::string &command);
};

#endif

