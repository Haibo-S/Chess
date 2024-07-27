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
    // vector<Piece *> pieces;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Tile cell(i, j);
            if (i == 1 || i == 6) {
                Pawn *pawn = new Pawn(Team::W, i, j);
                pawn->setTeam((i%2) ? Team::W : Team::B);
                board[i][j].placePiece(pawn);
                // pieces.push_back(pawn);
            }
            if (i == 0 || i == 7) {
                if (j == 0 || j == 7) {
                    Rook *rook = new Rook(Team::W, i, j);
                    rook->setTeam((!(i == 0)) ? Team::B : Team::W);
                    board[i][j].placePiece(rook);
                    // pieces.push_back(rook);
                }
                if (j == 1 || j == 6){
                     Knight *knight  = new Knight(Team::W, i, j);
                     knight->setTeam((!(i == 0)) ? Team::B : Team::W);
                     board[i][j].placePiece(knight);
                    //  pieces.push_back(knight);
                 }
                 if (j == 2 || j == 5){
                     Bishop *bishop = new Bishop(Team::W, i, j);
                     bishop->setTeam((!(i == 0)) ? Team::B : Team::W);
                     board[i][j].placePiece(bishop);
                    //  pieces.push_back(bishop);
                 }
                if (j == 3) {
                     Queen *queen = new Queen(Team::W, i, j);
                     queen->setTeam((!(i == 0)) ? Team::B : Team::W);
                     board[i][j].placePiece(queen);
                    // pieces.push_back(queen);
                 }
                if (j == 4) {
                    King *king = new King(Team::W, i, j);
                    king->setTeam((!(i == 0)) ? Team::B : Team::W);
                    board[i][j].placePiece(king);
                    // pieces.push_back(king);
                }
            }
        }
    }
    // for ( auto &n : pieces ) {
    //     // n->setUpPieces(pieces);
    //     // n->removePiece(n);
    // }
}

bool Board::move(vector<int> from, vector<int> to){
    Piece *p = board[from[0]][from[1]].getPiece();
    board[to[0]][to[1]].placePiece(p);
    return true;
}


void Board::toggleTurn(){
    turn = turn == Team::W ? Team::B : Team::W;
}

ostream &operator<<(ostream &out, const Board &b){
    out << b.td;
    return out;
}

// void Board::setPiece(int row, int col, Piece *p){

// }

// void Board::detachPiece(int row, int col){

// }

// void Board::deletePiece(int row, int col){

// }

// Piece* Board::getPiece(int row, int col){
    
// }

vector<Piece*> Board::getAllWhitePieces(){
    vector<Piece*> result;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j].getPiece() != nullptr && board[i][j].getPiece()->getTeam() == Team::W){
                result.emplace_back(board[i][j].getPiece());
            }
        }
    }
    return result;
}

vector<Piece*> Board::getAllBlackPieces(){
    vector<Piece*> result;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j].getPiece() != nullptr && board[i][j].getPiece()->getTeam() == Team::B){
                result.emplace_back(board[i][j].getPiece());
            }
        }
    }
    return result;
}

vector<Piece*> Board::getAllKingPieces(){
    vector<Piece*> result;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j].getPiece() != nullptr && board[i][j].getPiece()->getPieceType() == PieceType::KING){
                result.emplace_back(board[i][j].getPiece());
            }
        }
    }
    return result;
}

vector<Piece*> Board::getAllPieces(){
    vector<Piece*> result;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j].getPiece() != nullptr){
                result.emplace_back(board[i][j].getPiece());
            }
        }
    }
    return result;
}
