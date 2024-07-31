#include "./../include/level5.h"
#include <cstdlib>
#include <ctime>

// Assert if the position is capturable by the enemy
bool Level5::isCapturable(std::vector<std::vector<char>>board2, int row, int col) {

    bool isWhite = (team == Team::W);
    
    return game->isAttackedByPawn(board2, row, col, isWhite) ||
           game->isAttackedByKnight(board2, row, col, isWhite) ||
           game->isAttackedBySlidingPiece(board2, row, col, isWhite, {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}, 'R', 'Q') ||
           game->isAttackedBySlidingPiece(board2, row, col, isWhite, {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}}, 'B', 'Q');
}

// Evaluate which move is the best
int Level5::evaluate(std::vector<std::vector<char>>board2, int r1, int c1, int r2, int c2) {
    Piece* p1 = board->getTile(r1, c1).getPiece();
    Piece* p2 = board->getTile(r2, c2).getPiece();

    int moveScore = 0;

    

    // Assign a weight to each move based on the number of points that can be gained/lost through the move
    int moveValue = isCapturable(board2, r2, c2) ? getVal(p1->getPieceType()) : 0;
    int saveValue = (isCapturable(game->printTable(),r1 , c1) && !isCapturable(board2,r2,c2)) ? getVal(p1->getPieceType()) : 0;
    int captureValue = (p2 != nullptr) ? getVal(p2->getPieceType()) : 0;

    moveScore = captureValue - moveValue + saveValue;

    std::vector<std::vector<char>> textdisplay = game->printTable();
    char fillChar = textdisplay[r1][c1];
    textdisplay[r2][c2] = fillChar;
    textdisplay[r1][c1] = ' ';

    // Putting the king in a check position is the lowest possible score, so this will be an impossibility
    if (game->isKingInCheck(textdisplay, team == Team::W)) {
        return -9999999;
    }

    return moveScore;
}

// Get the value of each piece
int Level5::getVal(PieceType type) {
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

void Level5::turn() {
    std::vector<std::vector<char>> chardisplay = game->printTable();
    std::vector<std::pair<std::vector<int>, int>> moveList;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board->getTile(i, j).getPiece();
            if (piece && piece->getTeam() == team) {
                auto pieceMoves = piece->fetchAllMoves();
                for (const auto& move : pieceMoves) {
                    if (game->simpleIsValidMove(i, j, move[0], move[1])) {
                        // Temp board
                        std::vector<std::vector<char>> textdisplay = game->printTable();
                        char fillChar = textdisplay[i][j];
                        textdisplay[move[0]][move[1]] = fillChar;
                        textdisplay[i][j] = ' ';

                        if (game->isKingInCheck(textdisplay, team == Team::W)) {
                            continue;
                        }

                        int moveValue = evaluate(textdisplay,i, j, move[0], move[1]);
                        moveList.push_back({{i, j, move[0], move[1]}, moveValue});
                    }
                }
            }
        }
    }

    // Sort the moves list by getting the "best move" in front
    for (size_t i = 0; i < moveList.size(); ++i) {
        for (size_t j = 0; j < moveList.size() - 1; ++j) {
            if (moveList[j].second < moveList[j + 1].second) {
                std::swap(moveList[j], moveList[j + 1]);
            }
        }
    }

    std::vector<std::pair<std::vector<int>, int>>* preferredMoves = &moveList;

    // Get the best move

    if (!preferredMoves->empty()) {
        auto move = (*preferredMoves)[0].first;
        std::string movecommand = "move " + std::string(1, 'a' + move[1]) + std::to_string(8 - move[0]) + " " +
                                  std::string(1, 'a' + move[3]) + std::to_string(8 - move[2]);
        std::cout << "Computer's turn: " + movecommand << std::endl;
        game->commandHandler(movecommand);
    }
}
