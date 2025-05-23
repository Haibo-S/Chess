#include "./../../Board/include/board.h"



using namespace std;

void Board::init(){
    board.clear();

    turn = Team::W;

    for (int i = 0; i < 8; i++) { 
        vector<Tile> temp;
        for (int j = 0; j < 8; j++) { 
            Tile cell(i,j); 
            if ((i + j) % 2 == 0) {
                cell.setColour(Colour::B);
            } else {
                cell.setColour(Colour::W);
            }
            // add observer to this cell
            cell.attach(&td);
            cell.attach(&gd);

            temp.push_back(cell);
        }
        board.push_back(temp);
    }


}


void Board::initDefault(){

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Tile cell(i, j);
            if (i == 1 || i == 6) {
                Pawn *pawn = new Pawn(Team::W, i, j);
                pawn->setTeam((i==6) ? Team::W : Team::B);
                board[i][j].placePiece(pawn);
            }
            if (i == 0 || i == 7) {
                if (j == 0 || j == 7) {
                    Rook *rook = new Rook(Team::W, i, j);
                    rook->setTeam(((i == 0)) ? Team::B : Team::W);
                    board[i][j].placePiece(rook);
                }
                if (j == 1 || j == 6){
                     Knight *knight  = new Knight(Team::W, i, j);
                     knight->setTeam(((i == 0)) ? Team::B : Team::W);
                     board[i][j].placePiece(knight);
                 }
                 if (j == 2 || j == 5){
                     Bishop *bishop = new Bishop(Team::W, i, j);
                     bishop->setTeam(((i == 0)) ? Team::B : Team::W);
                     board[i][j].placePiece(bishop);
                 }
                if (j == 3) {
                     Queen *queen = new Queen(Team::W, i, j);
                     queen->setTeam(((i == 0)) ? Team::B : Team::W);
                     board[i][j].placePiece(queen);
                 }
                if (j == 4) {
                    King *king = new King(Team::W, i, j);
                    king->setTeam(((i == 0)) ? Team::B : Team::W);
                    board[i][j].placePiece(king);
                }
            }
        }
    }

}

void Board::placeBoardPiece(int r, int c, char p, bool team){
    // team: true if white; false is black
    if(p == 'P'){
        Pawn *pawn = new Pawn(Team::W, r, c);
        pawn->setTeam(team ? Team::W : Team::B);
        board[r][c].placePiece(pawn);
    }else if(p == 'Q'){
        Queen *queen = new Queen(Team::W, r, c);
        queen->setTeam(team ? Team::W : Team::B);
        board[r][c].placePiece(queen);

    }else if(p == 'B'){
        Bishop *bishop = new Bishop(Team::W, r, c);
        bishop->setTeam(team ? Team::W : Team::B);
        board[r][c].placePiece(bishop);

    }else if(p == 'N'){
        Knight *knight = new Knight(Team::W, r, c);
        knight->setTeam(team ? Team::W : Team::B);
        board[r][c].placePiece(knight);

    }else if(p == 'R'){
        Rook *rook = new Rook(Team::W, r, c);
        rook->setTeam(team ? Team::W : Team::B);
        board[r][c].placePiece(rook);

    }else if(p == 'K'){
        King *king = new King(Team::W, r, c);
        king->setTeam(team ? Team::W : Team::B);
        board[r][c].placePiece(king);
    }
}


Tile& Board::getTile(int r, int c){
    return board[r][c];

}
bool Board::move(vector<int> from, vector<int> to){
    Piece *p = board[from[0]][from[1]].getPiece();
    board[from[0]][from[1]].removePiece();
    p->move(to[0],to[1]);
    board[to[0]][to[1]].placePiece(p);
    return true;
}

bool Board::removePiece(vector<int> coord){
    board[coord[0]][coord[1]].removePiece();
    return true;
}

void Board::clearBoard(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j].removePiece();
        }
    }
}


void Board::toggleTurn(){
    turn = turn == Team::W ? Team::B : Team::W;
}

ostream &operator<<(ostream &out, const Board &b){
    out << b.td;
    return out;
}


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
