#include "./../include/level3.h"
#include <cstdlib>
#include <ctime>

//check if the position is attackable by any of the enemy's pieces
bool Level3::isCapturable(std::vector<std::vector<char>>board2, int row, int col){
        bool isWhite = (team == Team::W);

    return game->isAttackedByPawn(board2, row, col, isWhite) ||
           game->isAttackedByKnight(board2, row, col, isWhite) ||
           game->isAttackedBySlidingPiece(board2, row, col, isWhite, {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}, 'R', 'Q') ||
           game->isAttackedBySlidingPiece(board2, row, col, isWhite, {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}}, 'B', 'Q');

}

void Level3::turn() {

    std::vector<std::vector<int>> avoidCaptureMoves;
    std::vector<std::vector<int>> dontDie;
    std::vector<std::vector<int>> capturingMoves;
    std::vector<std::vector<int>> checkingMoves;
    std::vector<std::vector<int>> otherMoves;



    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board->getTile(i, j).getPiece();
            if (piece && piece->getTeam() == team) {
                auto pieceMoves = piece->fetchAllMoves();
                for (const auto& move : pieceMoves) {
                    if (game->isValidMove(i, j, move[0], move[1])) {

                        //temp board
                       std::vector<std::vector<char>> textdisplay = game->printTable();
                        char fillChar = textdisplay[i][j];
                        textdisplay[move[0]][move[1]] = fillChar;
                        textdisplay[i][j] = ' ';

                        //dont move into check
                        if (game->isKingInCheck(textdisplay, team == Team::W)) {
                            continue;
                        }

                        //prio 1 is to avoid capture. we make sure that we are currently capturable and the position
                        //we are moving to is not a capturable position

                        if(isCapturable(game->printTable(),i,j) && !isCapturable(textdisplay,move[0], move[1])){
                            avoidCaptureMoves.push_back({i, j, move[0], move[1]});
                        }

                        //prio 2 is to capture enemy
                        else if (board->getTile(move[0], move[1]).getPiece() != nullptr) {
                            capturingMoves.push_back({i, j, move[0], move[1]});
                        } 
                        //prio 3 is to put enemy in check
                        else if (game->isCheck()) {
                            checkingMoves.push_back({i, j, move[0], move[1]});
                        } 
                        else if(!isCapturable(textdisplay,move[0],move[1])){
                            dontDie.push_back({i, j, move[0], move[1]});
                        }
                        //prio 4 is anything else
                        else {
                            otherMoves.push_back({i, j, move[0], move[1]});
                        }

                    }
                }
            }
        }
    }


    std::vector<std::vector<int>>* preferredMoves = &otherMoves;
    if(!avoidCaptureMoves.empty()){
        preferredMoves = &avoidCaptureMoves;
    }

    else if (!capturingMoves.empty()) {
        preferredMoves = &capturingMoves;
    } 
    else if (!checkingMoves.empty()) {
        preferredMoves = &checkingMoves;
    }
    else if(!dontDie.empty()){
        preferredMoves = &dontDie;
    }
    if (!preferredMoves->empty()) {
        auto move = (*preferredMoves)[std::rand() % preferredMoves->size()];
        std::string movecommand = "move " + std::string(1, 'a' + move[1]) + std::to_string(8 - move[0]) + " " +
                                  std::string(1, 'a' + move[3]) + std::to_string(8 - move[2]);
        std::cout<<"Computer's turn: " + movecommand << std::endl;
        game->commandHandler(movecommand);
    }


}
