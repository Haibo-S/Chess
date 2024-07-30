#include "./../include/level2.h"
#include <cstdlib>
#include <ctime>


void Level2::turn() {
    std::vector<std::vector<int>> capturingMoves;
    std::vector<std::vector<int>> checkingMoves;
    std::vector<std::vector<int>> otherMoves;

    //get all legal moves
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board->getTile(i, j).getPiece();
            if (piece && piece->getTeam() == team) {
                auto pieceMoves = piece->fetchAllMoves();
                for (const auto& move : pieceMoves) {
                    if (game->isValidMove(i, j, move[0], move[1])) {

                        //get a temporary board to check future moves
                        std::vector<std::vector<char>> textdisplay = game->printTable();
                        char fillChar = textdisplay[i][j];
                        textdisplay[move[0]][move[1]] = fillChar;
                        textdisplay[i][j] = ' ';

                        //we cant move into check
                        if (game->isKingInCheck(textdisplay, team == Team::W)) {
                            continue;
                        }


                        //if we can capture a piece, that is prio 1
                        if (board->getTile(move[0], move[1]).getPiece() != nullptr) {
                            capturingMoves.push_back({i, j, move[0], move[1]});
                        } 
                        //next would be to put the enemy in check
                        else if (game->isCheck()) {
                            checkingMoves.push_back({i, j, move[0], move[1]});
                        } 
                        //then would be any other legal move
                        else {
                            otherMoves.push_back({i, j, move[0], move[1]});
                        }


                    }
                }
            }
        }
    }

    std::vector<std::vector<int>>* preferredMoves = &otherMoves;
    if (!capturingMoves.empty()) {
        preferredMoves = &capturingMoves;
    } else if (!checkingMoves.empty()) {
        preferredMoves = &checkingMoves;
    }

    if (!preferredMoves->empty()) {
        auto move = (*preferredMoves)[std::rand() % preferredMoves->size()];
        std::string movecommand = "move " + std::string(1, 'a' + move[1]) + std::to_string(8 - move[0]) + " " +
                                  std::string(1, 'a' + move[3]) + std::to_string(8 - move[2]);
        std::cout<<"Computer's turn: " + movecommand << std::endl;
        game->commandHandler(movecommand);
    }
}
