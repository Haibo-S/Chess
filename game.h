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
#include "Player/include/level5.h"
#include <iostream>
#include <string>

extern bool isEnpassantMove;
extern bool isCassleMove;

class Game
{

    Board board;
    Team cur;
    vector<vector<int>> prevMove;
    vector<vector<char>> textdisplay;
    Player *whitePlayer = nullptr;
    Player *blackPlayer = nullptr;
    Player *curPlayer;

    double whiteScore = 0;
    double blackScore = 0;

    void switchTurn();

    void moveCommand(const std::string &command);
    bool isPathObstructed(int r1, int c1, int r2, int c2);

    void printScore();

    vector<vector<int>> resolveCheckMoves();
    vector<vector<int>> allPossibleMoves();

public:
    Game() : cur{Team::W}, board{500}, whitePlayer{nullptr}, blackPlayer{nullptr}
    {
        board.init();
    };
    ~Game();
    bool isValidMove(int r1, int c1, int r2, int c2);
    bool isCheck();
    bool simpleIsValidMove(int r1, int c1, int r2, int c2);

    bool isKingInCheck(const vector<vector<char>> &board, bool isWhite);
    bool isValid(int x, int y);
    bool isAttackedByPawn(const vector<vector<char>> &board, int x, int y, bool isWhite);
    bool isAttackedByKnight(const vector<vector<char>> &board, int x, int y, bool isWhite);
    bool isAttackedBySlidingPiece(const vector<vector<char>> &board, int x, int y, bool isWhite, const vector<pair<int, int>> &directions, char piece1, char piece2);
    vector<vector<char>> printTable();

    void start();
    void commandHandler(const std::string &command);
    bool setUpHandler(const std::string &command);
};

#endif
