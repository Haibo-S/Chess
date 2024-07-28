#include "game.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

Game::Game() : cur{Team::W}, board{500} {
    board.init();
    board.initDefault();
}

void Game::start() {
    std::string command;
    while (true) {
        std::cout << (cur == Team::W ? "White's" : "Black's") << " turn. Enter command: ";
        std::getline(std::cin, command);
        commandHandler(command);
    }
}

void Game::commandHandler(const std::string &command) {
    if (command == "exit") {
        std::cout << "Exiting game." << std::endl;
        exit(0);
    } else if (command.substr(0, 4) == "move") {
        moveCommand(command);
    } else if (command == "resign") {
        std::cout << (cur == Team::W ? "White" : "Black") << " resigns. "
                  << (cur == Team::W ? "Black" : "White") << " wins!" << std::endl;
        exit(0);
    }
    // Add more commands as needed
}

void Game::moveCommand(const std::string &command) {
    // Parse the command to get start and end positions
    // Example: move e2 e4
    std::istringstream iss(command);
    std::string token;
    std::vector<std::string> tokens;
    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens.size() != 3) {
        std::cout << "Invalid command format. Use: move <start> <end>" << std::endl;
        return;
    }

    int r1 = 8 - (tokens[1][1] - '1');
    int c1 = tokens[1][0] - 'a';
    int r2 = 8 - (tokens[2][1] - '1');
    int c2 = tokens[2][0] - 'a';

    if (isValidMove(r1, c1, r2, c2)) {
        board.move({r1, c1}, {r2, c2});
        if (isCheckmate()) {
            std::cout << "Checkmate! " << (cur == Team::W ? "White" : "Black") << " wins!" << std::endl;
            exit(0);
        } else if (isStalemate()) {
            std::cout << "Stalemate! It's a draw!" << std::endl;
            exit(0);
        } else if (isCheck()) {
            std::cout << (cur == Team::W ? "White" : "Black") << " is in check!" << std::endl;
        }
        switchTurn();
    } else {
        std::cout << "Invalid move. Try again." << std::endl;
    }
}

void Game::switchTurn() {
    cur = (cur == Team::W) ? Team::B : Team::W;
}

bool Game::isValidMove(int r1, int c1, int r2, int c2) {
    Tile& startTile = board.getTile(r1, c1);
    Tile& endTile = board.getTile(r2, c2);
    Piece* piece = startTile.getPiece();

    if (!piece || piece->getTeam() != cur) {
        return false;
    }

    std::vector<std::vector<int>> validMoves = piece->fetchAllMoves();
    for (const auto& move : validMoves) {
        if (move[0] == r2 && move[1] == c2) {

            if (piece->getPieceType() == PieceType::PAWN) {
                //check that nothing is blocking the path
                if (c1 == c2) {
                    if (endTile.getPiece() != nullptr) {
                        return false;
                    }
                } 
                else {
                    // check there is a piece to take with diagonal move
                    if (endTile.getPiece() == nullptr || endTile.getPiece()->getTeam() == cur) {
                        return false;
                    }
                }
            }

            // check the king wont move into check
            if (piece->getPieceType() == PieceType::KING) {
                if (checkCheck(r1, c1, r2, c2)) {
                    return false;
                }
            }
            return true;
        }

            if (piece->getPieceType() == PieceType::PAWN || piece->getPieceType() == PieceType::ROOK || piece->getPieceType() == PieceType::BISHOP || piece->getPieceType() == PieceType::QUEEN) {
                if (isPathObstructed(r1, c1, r2, c2)) {
                    return false;
                }
            }        
    }

    return false;
}

bool Game::isCheck() {

    //get location of the king
    Tile* kingTile = nullptr;


    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            Piece* temp = board.getTile(i,j).getPiece();

            if(temp != nullptr && temp->getPieceType() == PieceType::KING && temp->getTeam() == cur){
                kingTile = &board.getTile(i,j);
                break;
            }
        }
        if(kingTile != nullptr){
            break;
        }
    }


    //get list of all possible enemy moves. If one of those moves can capture the king then the king is in check
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            Piece* temp = board.getTile(i,j).getPiece();
            if(temp != nullptr && temp->getTeam() != cur){
                for(auto move: temp->fetchAllMoves()){
                    if(isValidMove(i,j,move[0],move[1])){
                    if(move[0] == kingTile->getRow() && move[1] == kingTile->getCol()){
                        return true;
                    }
                    }
                }
            }
        }
    }
    return false;
}

bool Game::isCheckmate() {
    if(isCheck() == false){
        return false;
    }


    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            Piece* temp = board.getTile(i,j).getPiece();
            if(temp != nullptr && temp->getTeam() != cur){
                for(auto move: temp->fetchAllMoves()){
                    int r2 = move[0];
                    int c2 = move[1];
                    if(isValidMove(i,j,r2,c2)){
                        Piece* capturedPiece = board.getTile(r2,c2).getPiece();
                        board.getTile(r2,c2).placePiece(temp);
                        bool inCheck = isCheck();

                        board.getTile(i,j).placePiece(temp);
                        board.getTile(r2,c2).placePiece(capturedPiece);

                        if(inCheck == false){
                            return false;
                        }
                    }

                }
            }  

        }
    }
    return true;
}

bool Game::isStalemate() {
    if(isCheck()){
        return false;
    }

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            Piece* temp = board.getTile(i,j).getPiece();
            if(temp != nullptr && temp->getTeam() != cur){
                for(auto move: temp->fetchAllMoves()){
                    int r2 = move[0];
                    int c2 = move[1];
                    if(isValidMove(i,j,r2,c2)){
                    Piece* capturedPiece = board.getTile(r2,c2).getPiece();
                    board.getTile(r2,c2).placePiece(temp);



                    bool isMoveValid = !isCheck();

                    board.getTile(i,j).placePiece(temp);
                    board.getTile(r2,c2).placePiece(capturedPiece);

                    if(isMoveValid){
                        return false;
                    }
                    }

                }
            }  

        }
    }    



    return false;
}


bool Game::checkCheck(int r1, int c1, int r2, int c2) {
    // Temporarily move the piece
    Tile& startTile = board.getTile(r1, c1);
    Tile& endTile = board.getTile(r2, c2);
    Piece* piece = startTile.getPiece();
    Piece* capturedPiece = endTile.getPiece();

    startTile.removePiece();
    endTile.placePiece(piece);

    bool inCheck = isCheck();

    // Undo the move
    endTile.removePiece();
    startTile.placePiece(piece);
    if (capturedPiece) {
        endTile.placePiece(capturedPiece);
    }

    return inCheck;
}


bool Game::isPathObstructed(int r1, int c1, int r2, int c2) {
    bool isDiagonal = false;
    int rowDirection = (r2 - r1) > 0 ? 1 : (r2 - r1) < 0 ? -1 : 0;
    int colDirection = (c2 - c1) > 0 ? 1 : (c2 - c1) < 0 ? -1 : 0;

    int currentRow = r1 + rowDirection;
    int currentCol = c1 + colDirection;

    if(rowDirection != 0 && colDirection != 0 ){
        isDiagonal = true;
    }

    while (currentRow != r2 || currentCol != c2) {
        if (board.getTile(currentRow, currentCol).getPiece() != nullptr) {
            return true;
        }
        currentRow += rowDirection;
        currentCol += colDirection;
    }

    return false;
}