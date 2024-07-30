#include "./../include/graphic.h"

Graphic::Graphic(int windowSize)
    : w{windowSize, windowSize},
      windowSize{windowSize},
      blockSize{(gridNum == 0) ? 0 : (windowSize - 100) / (gridNum + 1)} {
    initializeGrid();
}


void Graphic::initializeGrid() {
    for (int i = 0; i < gridNum; ++i) {
        w.drawString(50, 75 + i * blockSize, std::string(1, '8' - i));
        for (int j = 0; j < gridNum; ++j) {
            int xaxis = 50 + (j + 1) * blockSize;
            int yaxis = 50 + i * blockSize;
            if ((i + j) % 2 == 0) {
                w.fillRectangle(xaxis, yaxis, blockSize, blockSize, Xwindow::White);
            } else {
                w.fillRectangle(xaxis, yaxis, blockSize, blockSize, Xwindow::Black);
            }
        }
    }
    for (char c = 'a'; c <= 'h'; ++c) {
        int xaxis = 75 + (c - 'a' + 1) * blockSize;
        int yaxis = 100 + gridNum * blockSize;
        w.drawString(xaxis, yaxis, std::string(1, c));
    }
}


void Graphic::notify(Tile &tile) {
    int xaxis = 50 + (tile.getCol()+1) * blockSize;
    int yaxis = 50 + (tile.getRow()) * blockSize;
    char ch = drawChar(tile);
    if (ch == '_') { 
        w.fillRectangle(xaxis, yaxis, blockSize, blockSize, Xwindow::Black);
    }
    else if(ch == ' '){
        w.fillRectangle(xaxis, yaxis, blockSize, blockSize, Xwindow::White);
    }else{
        if(tile.getColour() == Colour::B){
            w.fillRectangle(xaxis, yaxis, blockSize, blockSize, Xwindow::White);
            w.drawString(xaxis + blockSize/2, yaxis + blockSize/2, std::string(1,ch), Xwindow::Black);
        }else{
            w.fillRectangle(xaxis, yaxis, blockSize, blockSize, Xwindow::Black);
            w.drawString(xaxis + blockSize/2, yaxis + blockSize/2, std::string(1,ch), Xwindow::White);
        }

    }
}



char Graphic::drawChar(Tile& tile) {
    if(tile.getPiece()==nullptr){
        return (tile.getCol() + tile.getRow()) % 2 == 0 ? ' ' : '_';
    }
    PieceType pt = tile.getPieceType();
    
    switch (pt) {
        case PieceType::NONE:
            return (tile.getCol() + tile.getRow()) % 2 == 0 ? ' ' : '_';
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


