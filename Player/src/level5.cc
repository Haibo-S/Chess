#include "./../include/level5.h"
#include <cstdlib>
#include <ctime>


int Level5::evaluate(int r1, int c1, int r2, int c2){
    Piece* p1 = board->getTile(r1,c1).getPiece();
    Piece* p2 = board->getTile(r2,c2).getPiece();

    int moveScore=0;

    int moveValue = isCapturable(r2,c2) ? getVal(p1->getPieceType()) : 0;
    int captureValue = (p2 != nullptr) ? getVal(p2->getPieceType()) : 0;

    moveScore = captureValue - moveValue;

    std::vector<std::vector<char>> textdisplay = game->printTable();
    char fillChar = textdisplay[r1][c1];
    textdisplay[r2][c2] = fillChar;
    textdisplay[r1][c2] = ' ';

    if (game->isKingInCheck(textdisplay, team == Team::W)) {
        return -9999999; 
    }

    return moveScore;

}
bool Level5::isCapturable(int row, int col){
    std::vector<std::vector<char>> board2 = game->printTable();
    return game->isAttackedByPawn(board2, row, col, false) ||
           game->isAttackedByKnight(board2, row, col, false) ||
           game->isAttackedBySlidingPiece(board2, row, col, false, {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}, 'R', 'Q') ||
           game->isAttackedBySlidingPiece(board2, row, col, false, {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}}, 'B', 'Q');

}
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
                    if (game->isValidMove(i, j, move[0], move[1])) {

                        // Tentative move
                        std::vector<std::vector<char>> textdisplay = game->printTable();
                        char fillChar = textdisplay[i][j];
                        textdisplay[move[0]][move[1]] = fillChar;
                        textdisplay[i][j] = ' ';

                        if (game->isKingInCheck(textdisplay, team == Team::W)) {
                            continue;
                        }

                        int moveValue = evaluate(i, j, move[0], move[1]);
                        moveList.push_back({{i, j, move[0], move[1]}, moveValue});

                    }
                }
            }
        }
    }


    for (size_t i = 0; i < moveList.size(); ++i) {
        for (size_t j = 0; j < moveList.size() - 1; ++j) {
            if (moveList[j].second < moveList[j + 1].second) {
                std::swap(moveList[j], moveList[j + 1]);
            }
        }
    }

    std::vector<std::pair<std::vector<int>, int>>* preferredMoves = &moveList;

    
    if (!preferredMoves->empty()) {
        auto move = (*preferredMoves)[std::rand() % preferredMoves->size()].first;
        std::string movecommand = "move " + std::string(1, 'a' + move[1]) + std::to_string(8 - move[0]) + " " +
                                  std::string(1, 'a' + move[3]) + std::to_string(8 - move[2]);
        std::cout<<"Computer's turn: " + movecommand << std::endl;
        game->commandHandler(movecommand);
    }


}
