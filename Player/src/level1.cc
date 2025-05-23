#include "./../include/level1.h"
#include <cstdlib>
#include <ctime>



void Level1::turn() {

    //get all legal moves
    std::vector<std::vector<int>> moves;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board->getTile(i, j).getPiece();
            if (piece && piece->getTeam() == team) {
                auto pieceMoves = piece->fetchAllMoves();
                for (const auto& move : pieceMoves) {
                    if (game->isValidMove(i, j, move[0], move[1])) {
                        moves.push_back({i, j, move[0], move[1]});
                    }
                }
            }
        }
    }

    //randomly select a move
    if (!moves.empty()) {
        auto move = moves[std::rand() % moves.size()];


        std::string movecommand = "move " + std::string(1, 'a' + move[1]) + std::to_string(8 - move[0]) + " " + std::string(1, 'a' + move[3]) + std::to_string(8 - move[2]);
        game->commandHandler(movecommand);
    }
}
