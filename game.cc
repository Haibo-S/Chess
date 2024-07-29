#include "game.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool isEnpassantMove = false;

void Game::start() {
    std::string command;
    while (true) {
        std::cout << (cur == Team::W ? "White's" : "Black's") << " turn. Enter command: ";
        std::getline(std::cin, command);
        commandHandler(command);
    }
}

string printTeam(const Team& t){
    return t == Team::W ? "W" : "B";
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

bool Game::setUpHandler(const std::string &command){
    std::istringstream iss(command);
    std::string token;
    std::vector<std::string> tokens;
    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens[0] == "done"){

        // More to be done here!
        return false;
    }else if (tokens[0] == "+"){
        if(!(tokens[1] == "Q" || tokens[1] == "B" || tokens[1] == "R" \
        || tokens[1] == "N" || tokens[1] == "P" || tokens[1] == "K" \
        || tokens[1] == "q" || tokens[1] == "b" || tokens[1] == "r" \
        || tokens[1] == "n" || tokens[1] == "p" || tokens[1] == "k" ) \
        || (tokens[2][0] < 'a' || tokens[2][0] > 'h') \
        || (tokens[2][1] < '1' || tokens[2][1] > '8') \
        ){
            std::cout << "Invalid Setup Input!" << std::endl;
            return true;
        }

        int r1 = 7 - (tokens[2][1] - '1');
        int c1 = tokens[2][0] - 'a';
        char piece = toupper(tokens[1][0]);
        bool team = !islower(tokens[1][0]);

        board.placeBoardPiece(r1, c1, piece, team);
    }else if (tokens[0] == "-"){
        if((tokens[1][0] < 'a' || tokens[1][0] > 'h') \
        || (tokens[1][1] < '1' || tokens[1][1] > '8')){
            std::cout << "Invalid Setup Input!" << std::endl;
            return true;
        }

        int r1 = 7 - (tokens[1][1] - '1');
        int c1 = tokens[1][0] - 'a';

        if(board.getTile(r1,c1).getPiece() == nullptr){
            return true;
        }else{
            board.removePiece({r1, c1});
        }

    }else if (tokens[0] == "="){
        if(tokens[1] != "w" && tokens[1] != "W" && tokens[1] != "b" && tokens[1] != "B"){
            std::cout << "Invalid Setup Input!" << std::endl;
            return true;
        }
        this->cur = tokens[1] == "w" || tokens[1] == "W" ? Team::W : Team::B;
        std::cout << "Turn is set to: " << ((tokens[1] == "w" || tokens[1] == "W") ? "White" : "Black") << std::endl;
    }else if (tokens[0] == "default"){
        board.initDefault();
        std::cout << "Setup Default ChessBoard" << std::endl;
    }else{
        std::cout << "Invalid Setup Input!" << std::endl;
    }
    return true;
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

    if (tokens.size() != 3 && tokens.size() != 4) {
        std::cout << "Invalid command format. Use: move <start> <end>" << std::endl;
        return;
    } else if(tokens.size() == 4){
        // Promotion Move

       if (tokens[0] != "move" || 
        (tokens[1][0] < 'a' || tokens[1][0] > 'h') ||
        (tokens[2][0] < 'a' || tokens[2][0] > 'h') ||
        (tokens[1][1] != '2' && tokens[1][1] != '7') ||
        (tokens[2][1] != '1' && tokens[2][1] != '8') ||
        !(tokens[3][0] == 'Q' || tokens[3][0] == 'B' || tokens[3][0] == 'R' || tokens[3][0] == 'N')) {
            std::cout << "Invalid command format. Make sure columns are a-h and rows are 1-8. Promotion can only be Q, B, N, R" << std::endl;
            return;
        }
        int r1 = 7 - (tokens[1][1] - '1');
        int c1 = tokens[1][0] - 'a';
        int r2 = 7 - (tokens[2][1] - '1');
        int c2 = tokens[2][0] - 'a';
        char promo = tokens[3][0];

        if(board.getTile(r1,c1).getPiece() == nullptr || board.getTile(r1,c1).getPieceType() != PieceType::PAWN){
            std::cout << "Invalid Move. Promotion must be a pawn"<<std::endl;
            return;
        }

        Team team = board.getTile(r1,c1).getPiece()->getTeam();

        if (isValidMove(r1, c1, r2, c2)) {
            board.move({r1, c1}, {r2, c2});
            board.removePiece({r2, c2});
            board.placeBoardPiece(r2, c2, promo, team == Team::W ? true : false);
        }else {
            std::cout << "Invalid move. Try again." << std::endl;
            return;
        }

        // Just like before
        if (isCheckmate()) {
            std::cout << "Checkmate! " << (cur == Team::W ? "White" : "Black") << " wins!" << std::endl;
            exit(0);
        } else if (isStalemate()) {
            std::cout << "Stalemate! It's a draw!" << std::endl;
            exit(0);
        } else if (isCheck()) {
            std::cout << (cur == Team::W ? "White" : "Black") << " is in check!" << std::endl;
        }

        prevMove = {{r1, c1}, {r2, c2}};
        switchTurn();

    }else{
        // Non Promotion Move
        // Invalid Input
        if(tokens[0] != "move" || (tokens[1][0] < 'a' || tokens[1][0] > 'h') \
        || (tokens[2][0] < 'a' || tokens[2][0] > 'h') \
        || (tokens[1][1] < '1' || tokens[1][1] > '8') \
        || (tokens[2][1] < '1' || tokens[2][1] > '8') ){
            std::cout << "Invalid command format. Make Sure col are a-h and row are 1-8" << std::endl;
            return;
        }

        int r1 = 7 - (tokens[1][1] - '1');
        int c1 = tokens[1][0] - 'a';
        int r2 = 7 - (tokens[2][1] - '1');
        int c2 = tokens[2][0] - 'a';

        if(board.getTile(r1,c1).getPiece() == nullptr){
            std::cout << "Space is empty, please call move on a tile with a piece."<<std::endl;
            return;
        }
        if (isValidMove(r1, c1, r2, c2)) {
            board.move({r1, c1}, {r2, c2});
            if(isEnpassantMove){
                board.removePiece({r1, c2});
                isEnpassantMove = false;
            }
            if (isCheckmate()) {
                std::cout << "Checkmate! " << (cur == Team::W ? "White" : "Black") << " wins!" << std::endl;
                exit(0);
            } else if (isStalemate()) {
                std::cout << "Stalemate! It's a draw!" << std::endl;
                exit(0);
            } else if (isCheck()) {
                std::cout << (cur == Team::W ? "White" : "Black") << " is in check!" << std::endl;
            }

            prevMove = {{r1, c1}, {r2, c2}};
            switchTurn();
        } else {
            std::cout << "Invalid move. Try again." << std::endl;
        }

    }

    
}

void Game::switchTurn() {
    cur = (cur == Team::W) ? Team::B : Team::W;
}

bool Game::isValidMove(int r1, int c1, int r2, int c2) {
    Tile& startTile = board.getTile(r1, c1);
    Tile& endTile = board.getTile(r2, c2);
    Piece* piece = startTile.getPiece();

    // std::cout << printTeam(piece->getTeam()) << " " << printTeam(cur) << std::endl;

    if (!piece || piece->getTeam() != cur) {
        return false;
    }

    std::vector<std::vector<int>> validMoves = piece->fetchAllMoves();

    // for(auto& move: validMoves){
    //     cout << move[0] << " " << move[1] << endl;
    // }

    // cout << "reached here" << endl;

    for (auto& move : validMoves) {
        if (move[0] == r2 && move[1] == c2) {

            if (piece->getPieceType() == PieceType::PAWN) {
                Pawn* pawn = dynamic_cast<Pawn*>(piece);

                //check that nothing is blocking the path
                if (c1 == c2) {
                    if (endTile.getPiece() != nullptr) {
                        return false;
                    }
                    if (pawn->getHasMoved() == true && (r2 - r1 >= 2)){
                        return false;
                    }
                } 
                else {
                    // check there is a piece to take with diagonal move

                    if ((endTile.getPiece() == nullptr && pawn->getEnPassant() == false)
                    || (endTile.getPiece() != nullptr && endTile.getPiece()->getTeam() == cur)) {
                        return false;
                    }

                    // enPassant
                    if(pawn->getEnPassant()){
                        // cout << "Reached Here" << endl;
                        if(c1 == 0){
                            if( cur == Team::W \
                            && r2 == r1 - 1 && c2 == c1 + 1 && endTile.getPiece() == nullptr \
                            && board.getTile(r1, c2).getPieceType() == PieceType::PAWN  &&  board.getTile(r1, c2).getPiece()->getTeam() != cur \
                            && prevMove[0][0] == r1 - 2 && prevMove[0][1] == c2 && prevMove[1][0] == r1 && prevMove[1][1] == c2){
                                pawn->setEnPassant(false);
                                isEnpassantMove = true;
                                return true;
                            }else if( cur == Team::B \
                            && r2 == r1 + 1 && c2 == c1 + 1 && endTile.getPiece() == nullptr \
                            && board.getTile(r1, c2).getPieceType() == PieceType::PAWN  &&  board.getTile(r1, c2).getPiece()->getTeam() != cur \
                            && prevMove[0][0] == r1 + 2 && prevMove[0][1] == c2 && prevMove[1][0] == r1 && prevMove[1][1] == c2){
                                pawn->setEnPassant(false);
                                isEnpassantMove = true;
                                return true;
                            }else{
                                isEnpassantMove = false;
                                return false;
                            }
                        }else if(c1 == 7){
                            if( cur == Team::W \
                            && r2 == r1 - 1 && c2 == c1 - 1 && endTile.getPiece() == nullptr \
                            && board.getTile(r1, c2).getPieceType() == PieceType::PAWN  &&  board.getTile(r1, c2).getPiece()->getTeam() != cur \
                            && prevMove[0][0] == r1 - 2 && prevMove[0][1] == c2 && prevMove[1][0] == r1 && prevMove[1][1] == c2){
                                pawn->setEnPassant(false);
                                isEnpassantMove = true;
                                return true;
                            }else if( cur == Team::B \
                            && r2 == r1 + 1 && c2 == c1 - 1 && endTile.getPiece() == nullptr \
                            && board.getTile(r1, c2).getPieceType() == PieceType::PAWN  &&  board.getTile(r1, c2).getPiece()->getTeam() != cur \
                            && prevMove[0][0] == r1 + 2 && prevMove[0][1] == c2 && prevMove[1][0] == r1 && prevMove[1][1] == c2){
                                pawn->setEnPassant(false);
                                isEnpassantMove = true;
                                return true;
                            }else{
                                isEnpassantMove = false;
                                return false;
                            }
                        }else{
                            if( cur == Team::W \
                            && r2 == r1 - 1 && c2 == c1 + 1 && endTile.getPiece() == nullptr \
                            && board.getTile(r1, c2).getPieceType() == PieceType::PAWN  &&  board.getTile(r1, c2).getPiece()->getTeam() != cur \
                            && prevMove[0][0] == r1 - 2 && prevMove[0][1] == c2 && prevMove[1][0] == r1 && prevMove[1][1] == c2){
                                pawn->setEnPassant(false);
                                isEnpassantMove = true;
                                return true;
                            }else if( cur == Team::B \
                            && r2 == r1 + 1 && c2 == c1 + 1 && endTile.getPiece() == nullptr \
                            && board.getTile(r1, c2).getPieceType() == PieceType::PAWN  &&  board.getTile(r1, c2).getPiece()->getTeam() != cur \
                            && prevMove[0][0] == r1 + 2 && prevMove[0][1] == c2 && prevMove[1][0] == r1 && prevMove[1][1] == c2){
                                pawn->setEnPassant(false);
                                isEnpassantMove = true;
                                return true;
                            }else if( cur == Team::W \
                            && r2 == r1 - 1 && c2 == c1 - 1 && endTile.getPiece() == nullptr \
                            && board.getTile(r1, c2).getPieceType() == PieceType::PAWN  &&  board.getTile(r1, c2).getPiece()->getTeam() != cur \
                            && prevMove[0][0] == r1 - 2 && prevMove[0][1] == c2 && prevMove[1][0] == r1 && prevMove[1][1] == c2){
                                pawn->setEnPassant(false);
                                isEnpassantMove = true;
                                return true;
                            }else if( cur == Team::B \
                            && r2 == r1 + 1 && c2 == c1 - 1 && endTile.getPiece() == nullptr \
                            && board.getTile(r1, c2).getPieceType() == PieceType::PAWN  &&  board.getTile(r1, c2).getPiece()->getTeam() != cur \
                            && prevMove[0][0] == r1 + 2 && prevMove[0][1] == c2 && prevMove[1][0] == r1 && prevMove[1][1] == c2){
                                pawn->setEnPassant(false);
                                isEnpassantMove = true;
                                return true;
                            }else{
                                isEnpassantMove = false;
                                return false;
                            }
                            
                        }
                    }


                }

                if(!dynamic_cast<Pawn*>(piece)->getEnPassant() &&  piece->getTeam() == Team::W && r2 == 3){
                    // std::cout << "Setting EnPassant!" << std::endl;
                    dynamic_cast<Pawn*>(piece)->setEnPassant(true);
                }else if(!dynamic_cast<Pawn*>(piece)->getEnPassant() && piece->getTeam() == Team::B && r2 == 4){
                    // std::cout << "Setting EnPassant!" << std::endl;
                    dynamic_cast<Pawn*>(piece)->setEnPassant(true);
                }else{
                    dynamic_cast<Pawn*>(piece)->setEnPassant(false);
                }

                
            }

            // check the king wont move into check
            if (piece->getPieceType() == PieceType::KING) {
                if (checkCheck(r1, c1, r2, c2)) {
                    return false;
                }
            }

            piece->setHasMovedToTrue();
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


