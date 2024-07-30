#include "./../include/text.h"
#include <iostream>


Text::Text() {
    boardDisplay.resize(gridSize, std::vector<char>(gridSize, ' '));
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i + j) % 2 == 0)
                boardDisplay[i][j] = '_';
        }
    }
}

void Text::notify(Tile &tile) {
    boardDisplay[7-tile.getRow()][tile.getCol()] = printChar(tile);
    std::cout <<*this;
}

char Text::printChar(Tile& tile) {
    PieceType pt = tile.getPieceType();
    switch (pt) {
        case PieceType::NONE:
            return (tile.getCol() + tile.getRow()) % 2 == 0 ? '_' : ' ';
        case PieceType::KNIGHT: {
            Piece* p = tile.getPiece();
            Team tc = p->getTeam();
            return tc == Team::W ? 'N' : 'n';
        }
        case PieceType::PAWN: {
            Piece* p = tile.getPiece();
            Team tc = p->getTeam();
            return tc == Team::W ? 'P' : 'p';
        }
        case PieceType::KING: {
            Piece* p = tile.getPiece();
            Team tc = p->getTeam();
            return tc == Team::W ? 'K' : 'k';
        }
        case PieceType::BISHOP: {
            Piece* p = tile.getPiece();
            Team tc = p->getTeam();
            return tc == Team::W ? 'B' : 'b';
        }
        case PieceType::ROOK: {
            Piece* p = tile.getPiece();
            Team tc = p->getTeam();
            return tc == Team::W ? 'R' : 'r';
        }
        case PieceType::QUEEN: {
            Piece* p = tile.getPiece();
            Team tc = p->getTeam();
            return tc == Team::W ? 'Q' : 'q';
        }
        default:
            return 0;
    }
}

std::ostream &operator<<(std::ostream &out, const Text &text) {
    for (int r = text.gridSize - 1; r >= 0; --r) {
        out << r + 1 << ' ';
        for (int c = 0; c < text.gridSize; ++c) {
            out << text.boardDisplay[r][c];
        }
        out << std::endl;
    }
    out << std::endl;
    out << "  ABCEDEFGH" << std::endl;
    return out;
}



