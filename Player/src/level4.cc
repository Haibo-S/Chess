#include "./../include/level4.h"
#include <cstdlib>
#include <ctime>



void Level4::turn() {
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
    //     int bestScore = -10000;
    //     std::vector<int> bestMove;
    //     for (const auto& move : moves) {
    //         int r1 = move[0], c1 = move[1], r2 = move[2], c2 = move[3];
    //         // Evaluate move - placeholder evaluation function
    //         int score = std::rand() % 100;
    //         if (score > bestScore) {
    //             bestScore = score;
    //             bestMove = move;
    //         }
    //     }
    //     if (!bestMove.empty()) {
    //         game->moveCommand("move " + std::string(1, 'a' + bestMove[1]) + std::to_string(8 - bestMove[0]) + " " +
    //                           std::string(1, 'a' + bestMove[3]) + std::to_string(8 - bestMove[2]));
    //     }
    // }
}
