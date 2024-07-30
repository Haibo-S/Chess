#include "./../include/level2.h"
#include <cstdlib>
#include <ctime>


void Level2::turn() {
        std::cout<<"adwf";

    // std::vector<std::vector<int>> moves;
    // for (int i = 0; i < 8; ++i) {
    //     for (int j = 0; j < 8; ++j) {
    //         Piece* piece = board->getTile(i, j).getPiece();
    //         if (piece && piece->getTeam() == team) {
    //             auto pieceMoves = piece->fetchAllMoves();
    //             for (const auto& move : pieceMoves) {
    //                 if (game->isValidMove(i, j, move[0], move[1])) {
    //                     moves.push_back({i, j, move[0], move[1]});
    //                 }
    //             }
    //         }
    //     }
    // }
    // if (!moves.empty()) {
    //     for (const auto& move : moves) {
    //         int r1 = move[0], c1 = move[1], r2 = move[2], c2 = move[3];
    //         if (!board->getTile(r2, c2).getPiece()) {
    //             game->moveCommand("move " + std::string(1, 'a' + c1) + std::to_string(8 - r1) + " " +
    //                               std::string(1, 'a' + c2) + std::to_string(8 - r2));
    //             return;
    //         }
    //     }
    //     auto move = moves[std::rand() % moves.size()];
    //     game->moveCommand("move " + std::string(1, 'a' + move[1]) + std::to_string(8 - move[0]) + " " +
    //                       std::string(1, 'a' + move[3]) + std::to_string(8 - move[2]));
    // }
}
