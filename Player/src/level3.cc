#include "./../include/level3.h"
#include <cstdlib>
#include <ctime>

bool Level3::isCapturable(int row, int col){
    std::vector<std::vector<char>> board2 = game->printTable();
    return game->isAttackedByPawn(board2, row, col, false) ||
           game->isAttackedByKnight(board2, row, col, false) ||
           game->isAttackedBySlidingPiece(board2, row, col, false, {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}, 'R', 'Q') ||
           game->isAttackedBySlidingPiece(board2, row, col, false, {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}}, 'B', 'Q');

}

void Level3::turn() {

    std::vector<std::vector<int>> avoidCaptureMoves;
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
                        // Temporarily make the move
                        Tile& startTile = board->getTile(i, j);
                        Tile& endTile = board->getTile(move[0], move[1]);
                        Piece* capturedPiece = endTile.getPiece();
                        startTile.checkRemove();
                        endTile.checkPlace(piece);

                        if(isCapturable(i,j) && !isCapturable(move[0], move[1])){
                            avoidCaptureMoves.push_back({i, j, move[0], move[1]});
                        }
                        else if (capturedPiece) {
                            capturingMoves.push_back({i, j, move[0], move[1]});
                        } else if (game->isCheck()) {
                            checkingMoves.push_back({i, j, move[0], move[1]});
                        } else {
                            otherMoves.push_back({i, j, move[0], move[1]});
                        }

                        // Undo the move
                        endTile.checkRemove();
                        startTile.checkPlace(piece);
                        if (capturedPiece) {
                            endTile.checkPlace(capturedPiece);
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
