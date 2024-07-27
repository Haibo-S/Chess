#include "./../../Board/include/board.h"

using namespace std;

void Board::init(){
    board.clear();

    turn = Team::W;

    for (int i = 0; i < 8; i++) { // each row
        vector<Tile> temp;
        for (int j = 0; j < 8; j++) { // each col
            Tile cell(i,j); // temp obj of this cell
            if ((i + j) % 2 == 0) {
                cell.setColour(Colour::W);
            } else {
                cell.setColour(Colour::B);
            }
            // add observer to this cell
            cell.attach(&td);
            cell.attach(&gd);

            temp.push_back(cell);
        }
        board.push_back(temp);
    }
    // notify all observers
    for ( auto &row : board ) {
        for ( auto &cell : row ) {
            cell.notifyObservers(cell);
        }
    }

}


void Board::initDefault(){

}

bool Board::move(vector<int> from, vector<int> to){

}


void Board::toggleTurn(){

}

ostream &operator<<(ostream &out, const Board &b){

}

void Board::setPiece(int row, int col, Piece *p){

}

void Board::detachPiece(int row, int col){

}

void Board::deletePiece(int row, int col){

}

Piece* Board::getPiece(int row, int col){

}

vector<Piece*> Board::getAllWhitePieces(){

}

vector<Piece*> Board::getAllBlackPieces(){

}

vector<Piece*> Board::getAllKingPieces(){

}

vector<Piece*> Board::getAllPieces(){

}
