#include "./../include/level4.h"
#include <cstdlib>
#include <ctime>

bool Level4::isCapturable(int row, int col){
    std::vector<std::vector<char>> board2 = game->printTable();
    return game->isAttackedByPawn(board2, row, col, false) ||
           game->isAttackedByKnight(board2, row, col, false) ||
           game->isAttackedBySlidingPiece(board2, row, col, false, {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}, 'R', 'Q') ||
           game->isAttackedBySlidingPiece(board2, row, col, false, {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}}, 'B', 'Q');

}
int Level4::getVal(PieceType type) {
    switch (type) {
        case PieceType::PAWN: return 1;
        case PieceType::KNIGHT: return 3;
        case PieceType::BISHOP: return 3;
        case PieceType::ROOK: return 5;
        case PieceType::QUEEN: return 9;
        case PieceType::KING: return 99999;
        default: return 0;
    }
}
void Level4::turn() {
    std::vector<std::vector<char>> chardisplay = game->printTable();

    std::vector<std::pair<std::vector<int>, int>> avoidCaptureMoves;
    std::vector<std::pair<std::vector<int>, int>> capturingMoves;
    std::vector<std::pair<std::vector<int>, int>> checkingMoves;
    std::vector<std::pair<std::vector<int>, int>> otherMoves;



    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board->getTile(i, j).getPiece();
            if (piece && piece->getTeam() == team) {
                auto pieceMoves = piece->fetchAllMoves();
                for (const auto& move : pieceMoves) {
                    if (game->isValidMove(i, j, move[0], move[1])) {

                        // Tentative move
                        std::vector<std::vector<char>> textdisplay = game->printTable();
                        char fillChar = textdisplay[i][j];
                        textdisplay[move[0]][move[1]] = fillChar;
                        textdisplay[i][j] = ' ';

                        if (game->isKingInCheck(textdisplay, team == Team::W)) {
                            continue;
                        }

                        int pieceVal = getVal(piece->getPieceType());

                        if(isCapturable(i,j) && !isCapturable(move[0], move[1])){
                            avoidCaptureMoves.push_back({{i, j, move[0], move[1]},pieceVal});
                        }
                        else if (board->getTile(move[0], move[1]).getPiece() != nullptr) {
                            capturingMoves.push_back({{i, j, move[0], move[1]},pieceVal});
                        } else if (game->isCheck()) {
                            checkingMoves.push_back({{i, j, move[0], move[1]},pieceVal});
                        } else {
                            otherMoves.push_back({{i, j, move[0], move[1]},pieceVal});
                        }

                    }
                }
            }
        }
    }


    for (size_t i = 0; i < avoidCaptureMoves.size(); ++i) {
        for (size_t j = 0; j < avoidCaptureMoves.size() - 1; ++j) {
            if (avoidCaptureMoves[j].second < avoidCaptureMoves[j + 1].second) {
                std::swap(avoidCaptureMoves[j], avoidCaptureMoves[j + 1]);
            }
        }
    }

    std::vector<std::pair<std::vector<int>, int>>* preferredMoves = &otherMoves;
    if(!avoidCaptureMoves.empty()){
        preferredMoves = &avoidCaptureMoves;
    }
    else if (!capturingMoves.empty()) {
        preferredMoves = &capturingMoves;
    } else if (!checkingMoves.empty()) {
        preferredMoves = &checkingMoves;
    }

    if (!preferredMoves->empty()) {
        auto move = (*preferredMoves)[std::rand() % preferredMoves->size()].first;
        std::string movecommand = "move " + std::string(1, 'a' + move[1]) + std::to_string(8 - move[0]) + " " +
                                  std::string(1, 'a' + move[3]) + std::to_string(8 - move[2]);
        std::cout<<"Computer's turn: " + movecommand << std::endl;
        game->commandHandler(movecommand);
    }


}
