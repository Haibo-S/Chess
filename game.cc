#include "game.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <thread>

using namespace std;

bool isEnpassantMove = false;
bool isCassleMove = false;

Game::~Game()
{
    delete whitePlayer;
    if (blackPlayer)
        delete blackPlayer;
}

void Game::start()
{

    std::string playerType;
    std::cout << "Enter 'human' 'level1' 'level2' 'level3' 'level4' or 'level5' for the black player: ";
    std::cin >> playerType;
    whitePlayer = new Human(Team::W, &board, this, true);
    if (playerType == "human")
    {
        blackPlayer = new Human(Team::B, &board, this, false);
    }
    else if (playerType == "level1")
    {
        blackPlayer = new Level1(Team::B, &board, this, false);
    }
    else if (playerType == "level2")
    {
        blackPlayer = new Level2(Team::B, &board, this, false);
    }
    else if (playerType == "level3")
    {
        blackPlayer = new Level3(Team::B, &board, this, false);
    }
    else if (playerType == "level4")
    {
        blackPlayer = new Level4(Team::B, &board, this, false);
    }
    else if (playerType == "level5")
    {
        blackPlayer = new Level5(Team::B, &board, this, false);
    }
    else
    {
        std::cout << "Invalid player type. Defaulting to Level1 computer." << std::endl;
        blackPlayer = new Level1(Team::B, &board, this, false);
    }

    curPlayer = whitePlayer;
    bool setUpFlag = true;
    std::string line;
    std::cout << "Enter 'setup' to setup the board" << std::endl;
    while (getline(std::cin, line))
    {
        if (line == "setup")
            break;
    }
    std::cout << "Entered Setup Mode!" << std::endl;
    while (setUpFlag && getline(std::cin, line))
    {
        setUpFlag = setUpHandler(line);
    }
    std::cout << "Setup Mode Complete! Entering the Game!" << std::endl;
    if (cur == Team::B)
    {
        curPlayer = blackPlayer;
    }
    std::string command;
    while (true)
    {

        if (playerType == "human")
        {
            std::cout << (cur == Team::W ? "White's" : "Black's") << " turn. Enter command: ";
        }
        if (curPlayer == whitePlayer && playerType != "human")
        {
            std::cout << "Your turn. Enter command: ";
        }

        if (curPlayer == blackPlayer && playerType != "human")
        {
            std::cout << "Computer's move" << std::endl;
        }

        curPlayer->turn();
    }
}

void Game::printScore()
{
    cout << endl;
    cout << "Scores are the following: " << endl;
    cout << "White Score is: " << whiteScore << endl;
    cout << "Black Score is: " << blackScore << endl;
    cout << endl;
}

string printTeam(const Team &t)
{
    return t == Team::W ? "W" : "B";
}

void Game::commandHandler(const std::string &command)
{
    if (command == "exit")
    {
        std::cout << "Exiting game." << std::endl;
        printScore();
        exit(0);
    }
    else if (command.substr(0, 4) == "move")
    {
        moveCommand(command);
    }
    else if (command == "resign")
    {
        std::cout << (cur == Team::W ? "White" : "Black") << " resigns. "
                  << (cur == Team::W ? "Black" : "White") << " wins!" << std::endl;
        if (cur == Team::W)
        {
            blackScore += 1;
        }
        else
        {
            whiteScore += 1;
        }
        printScore();
        this_thread::sleep_for(std::chrono::seconds(5));
        board.clearBoard();
        board.initDefault();
        return;
    }
}

bool Game::setUpHandler(const std::string &command)
{
    std::istringstream iss(command);
    std::string token;
    std::vector<std::string> tokens;
    while (iss >> token)
    {
        tokens.push_back(token);
    }

    if (tokens[0] == "done")
    {

        // check for existence of two kings
        int whiteKingCount = 0;
        int blackKingCount = 0;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                Piece *temp = board.getTile(i, j).getPiece();
                if (temp != nullptr)
                {
                    if (temp->getPieceType() == PieceType::KING && temp->getTeam() == Team::W)
                    {
                        whiteKingCount++;
                    }
                    if (temp->getPieceType() == PieceType::KING && temp->getTeam() == Team::B)
                    {
                        blackKingCount++;
                    }
                }
            }
        }

        if (whiteKingCount != 1 || blackKingCount != 1)
        {
            cout << "Must have 1 black and white king!" << endl;
            return true;
        }

        // No king is in checked
        textdisplay = printTable();
        if (isKingInCheck(textdisplay, true) || isKingInCheck(textdisplay, false))
        {
            cout << "King is in checked!" << endl;
            return true;
        }

        return false;
    }
    else if (tokens[0] == "+")
    {
        if (!(tokens[1] == "Q" || tokens[1] == "B" || tokens[1] == "R" || tokens[1] == "N" || tokens[1] == "P" || tokens[1] == "K" || tokens[1] == "q" || tokens[1] == "b" || tokens[1] == "r" || tokens[1] == "n" || tokens[1] == "p" || tokens[1] == "k") || (tokens[2][0] < 'a' || tokens[2][0] > 'h') || (tokens[2][1] < '1' || tokens[2][1] > '8'))
        {
            std::cout << "Invalid Setup Input!" << std::endl;
            return true;
        }

        int r1 = 7 - (tokens[2][1] - '1');
        int c1 = tokens[2][0] - 'a';
        char piece = toupper(tokens[1][0]);
        bool team = !islower(tokens[1][0]);

        board.placeBoardPiece(r1, c1, piece, team);
    }
    else if (tokens[0] == "-")
    {
        if ((tokens[1][0] < 'a' || tokens[1][0] > 'h') || (tokens[1][1] < '1' || tokens[1][1] > '8'))
        {
            std::cout << "Invalid Setup Input!" << std::endl;
            return true;
        }

        int r1 = 7 - (tokens[1][1] - '1');
        int c1 = tokens[1][0] - 'a';

        if (board.getTile(r1, c1).getPiece() == nullptr)
        {
            return true;
        }
        else
        {
            board.removePiece({r1, c1});
        }
    }
    else if (tokens[0] == "=")
    {
        if (tokens[1] != "w" && tokens[1] != "W" && tokens[1] != "b" && tokens[1] != "B")
        {
            std::cout << "Invalid Setup Input!" << std::endl;
            return true;
        }
        this->cur = tokens[1] == "w" || tokens[1] == "W" ? Team::W : Team::B;
        std::cout << "Turn is set to: " << ((tokens[1] == "w" || tokens[1] == "W") ? "White" : "Black") << std::endl;
    }
    else if (tokens[0] == "default")
    {
        board.initDefault();
        std::cout << "Setup Default ChessBoard" << std::endl;
    }
    else
    {
        std::cout << "Invalid Setup Input!" << std::endl;
    }
    return true;
}

void Game::moveCommand(const std::string &command)
{
    // Parse the command to get start and end positions e.g move e2 e4
    
    std::istringstream iss(command);
    std::string token;
    std::vector<std::string> tokens;
    while (iss >> token)
    {
        tokens.push_back(token);
    }

    if (tokens.size() != 3 && tokens.size() != 4)
    {
        std::cout << "Invalid command format. Use: move <start> <end>" << std::endl;
        return;
    }
    else if (tokens.size() == 4)
    {
        // Promotion Move

        if (tokens[0] != "move" ||
            (tokens[1][0] < 'a' || tokens[1][0] > 'h') ||
            (tokens[2][0] < 'a' || tokens[2][0] > 'h') ||
            (tokens[1][1] != '2' && tokens[1][1] != '7') ||
            (tokens[2][1] != '1' && tokens[2][1] != '8') ||
            !(tokens[3][0] == 'Q' || tokens[3][0] == 'B' || tokens[3][0] == 'R' || tokens[3][0] == 'N'))
        {
            std::cout << "Invalid command format. Make sure columns are a-h and rows are 1-8. Promotion can only be Q, B, N, R" << std::endl;
            return;
        }
        int r1 = 7 - (tokens[1][1] - '1');
        int c1 = tokens[1][0] - 'a';
        int r2 = 7 - (tokens[2][1] - '1');
        int c2 = tokens[2][0] - 'a';
        char promo = tokens[3][0];

        if (board.getTile(r1, c1).getPiece() == nullptr || board.getTile(r1, c1).getPieceType() != PieceType::PAWN)
        {
            std::cout << "Invalid Move. Promotion must be a pawn" << std::endl;
            return;
        }

        Team team = board.getTile(r1, c1).getPiece()->getTeam();

        if (isValidMove(r1, c1, r2, c2))
        {
            board.move({r1, c1}, {r2, c2});
            board.removePiece({r2, c2});
            board.placeBoardPiece(r2, c2, promo, team == Team::W ? true : false);
        }
        else
        {
            std::cout << "Invalid move. Try again." << std::endl;
            return;
        }

        if (isCheck())
        {
            std::cout << (cur == Team::W ? "Black" : "White") << " is in check!" << std::endl;

            vector<vector<int>> res = resolveCheckMoves();

            if (res.size() == 0)
            {
                std::cout << "Checkmate! " << (cur == Team::W ? "White" : "Black") << " wins!" << std::endl;
                if (cur == Team::W)
                {
                    whiteScore += 1;
                }
                else
                {
                    blackPlayer += 1;
                }
                printScore();
                this_thread::sleep_for(std::chrono::seconds(5));
                board.clearBoard();
                board.initDefault();
                return;
            }
        }

        // stalemate check
        vector<vector<int>> allMoves = allPossibleMoves();
        if (allMoves.size() == 0)
        {
            std::cout << "StaleMate! This is a draw!" << std::endl;
            whiteScore += 0.5;
            blackScore += 0.5;
            printScore();
            this_thread::sleep_for(std::chrono::seconds(5));
            board.clearBoard();
            board.initDefault();
            return;
        }

        prevMove = {{r1, c1}, {r2, c2}};
        switchTurn();
    }
    else
    {
        // Non Promotion Move
        // Invalid Input
        if (tokens[0] != "move" || (tokens[1][0] < 'a' || tokens[1][0] > 'h') || (tokens[2][0] < 'a' || tokens[2][0] > 'h') || (tokens[1][1] < '1' || tokens[1][1] > '8') || (tokens[2][1] < '1' || tokens[2][1] > '8'))
        {
            std::cout << "Invalid command format. Make Sure col are a-h and row are 1-8" << std::endl;
            return;
        }

        int r1 = 7 - (tokens[1][1] - '1');
        int c1 = tokens[1][0] - 'a';
        int r2 = 7 - (tokens[2][1] - '1');
        int c2 = tokens[2][0] - 'a';

        if (board.getTile(r1, c1).getPiece() == nullptr)
        {
            std::cout << "Space is empty, please call move on a tile with a piece." << std::endl;
            return;
        }
        if (isValidMove(r1, c1, r2, c2))
        {

            // temp move
            textdisplay = printTable();
            char fillChar = textdisplay[r1][c1];
            textdisplay[r2][c2] = fillChar;
            textdisplay[r1][c1] = ' ';

            if (isKingInCheck(textdisplay, cur == Team::W))
            {
                cout << "Invalid Move! Currently in Check!" << endl;
                return;
            }

            board.move({r1, c1}, {r2, c2});
            if (isEnpassantMove)
            {
                board.removePiece({r1, c2});
                isEnpassantMove = false;
            }
            if (isCassleMove)
            {
                if (c2 == c1 + 2)
                {
                    Team t = board.getTile(r1, c1 + 3).getPiece()->getTeam();
                    board.removePiece({r1, c1 + 3});
                    board.placeBoardPiece(r1, c2 - 1, 'R', t == Team::W);
                }
                else
                {
                    Team t = board.getTile(r1, c1 - 4).getPiece()->getTeam();
                    board.removePiece({r1, c1 - 4});
                    board.placeBoardPiece(r1, c2 + 1, 'R', t == Team::W);
                }
                isCassleMove = false;
            }
            if (isCheck())
            {
                std::cout << (cur == Team::W ? "Black" : "White") << " is in check!" << std::endl;

                vector<vector<int>> res = resolveCheckMoves();

 

                if (res.size() == 0)
                {
                    std::cout << "Checkmate! " << (cur == Team::W ? "White" : "Black") << " wins!" << std::endl;
                    if (cur == Team::W)
                    {
                        whiteScore += 1;
                    }
                    else
                    {
                        blackPlayer += 1;
                    }
                    printScore();
                    this_thread::sleep_for(std::chrono::seconds(5));
                    board.clearBoard();
                    board.initDefault();
                    return;
                }
            }

            // stalemate check
            vector<vector<int>> allMoves = allPossibleMoves();
            if (allMoves.size() == 0)
            {
                std::cout << "StaleMate! This is a draw!" << std::endl;
                whiteScore += 0.5;
                blackScore += 0.5;
                printScore();
                this_thread::sleep_for(std::chrono::seconds(5));
                board.clearBoard();
                board.initDefault();
                return;
            }

            prevMove = {{r1, c1}, {r2, c2}};
            switchTurn();
        }
        else
        {
            std::cout << "Invalid move. Try again." << std::endl;
        }
    }
}

void Game::switchTurn()
{
    cur = (cur == Team::W) ? Team::B : Team::W;
    curPlayer = (curPlayer == whitePlayer) ? blackPlayer : whitePlayer;
}

bool Game::simpleIsValidMove(int r1, int c1, int r2, int c2)
{
    Tile &startTile = board.getTile(r1, c1);
    Tile &endTile = board.getTile(r2, c2);
    Piece *piece = startTile.getPiece();



    std::vector<std::vector<int>> validMoves = piece->fetchAllMoves();
    Team tempCur = cur == Team::B ? Team::W : Team::B;
    for (const auto &move : validMoves)
    {
        if (move[0] == r2 && move[1] == c2)
        {

            if (piece->getPieceType() == PieceType::PAWN)
            {
                // check that nothing is blocking the path
                if (c1 == c2)
                {
                    if (endTile.getPiece() != nullptr)
                    {
                        return false;
                    }
                }
                else
                {
                    // check there is a piece to take with diagonal move
                    if (endTile.getPiece() == nullptr || endTile.getPiece()->getTeam() == startTile.getPiece()->getTeam())
                    {
                        return false;
                    }
                }
            }

            if (endTile.getPiece() != nullptr && endTile.getPiece()->getTeam() == startTile.getPiece()->getTeam())
            {
                return false;
            }

            if (piece->getPieceType() == PieceType::KING)
            {
                if (c2 == c1 + 2 || c2 == c1 - 2)
                    return false;
            }

            return true;
        }

        if (piece->getPieceType() == PieceType::PAWN || piece->getPieceType() == PieceType::ROOK || piece->getPieceType() == PieceType::BISHOP || piece->getPieceType() == PieceType::QUEEN)
        {
            if (isPathObstructed(r1, c1, r2, c2))
            {
                return false;
            }
        }
    }

    return false;
}

bool Game::isValidMove(int r1, int c1, int r2, int c2)
{
    Tile &startTile = board.getTile(r1, c1);
    Tile &endTile = board.getTile(r2, c2);
    Tile &cassleTileR = board.getTile(r1, c1 + 1);
    Tile &cassleTileL = board.getTile(r1, c1 - 1);
    Piece *piece = startTile.getPiece();


    if (!piece || piece->getTeam() != cur)
    {
        return false;
    }

    std::vector<std::vector<int>> validMoves = piece->fetchAllMoves();



    for (auto &move : validMoves)
    {
        if (move[0] == r2 && move[1] == c2)
        {

            if (piece->getPieceType() == PieceType::PAWN)
            {
                Pawn *pawn = dynamic_cast<Pawn *>(piece);

                // check that nothing is blocking the path
                if (c1 == c2)
                {
                    if (endTile.getPiece() != nullptr)
                    {
                        return false;
                    }
                    if (pawn->getHasMoved() == true && (r2 - r1 >= 2))
                    {
                        return false;
                    }
                }
                else
                {
                    // check there is a piece to take with diagonal move

                    if ((endTile.getPiece() == nullptr && pawn->getEnPassant() == false) || (endTile.getPiece() != nullptr && endTile.getPiece()->getTeam() == cur))
                    {
                        return false;
                    }

                    // enPassant
                    if (pawn->getEnPassant())
                    {
                        cout << "Reached Here" << endl;
                        if (c1 == 0)
                        {
                            if (cur == Team::W && r2 == r1 - 1 && c2 == c1 + 1 && endTile.getPiece() == nullptr && board.getTile(r1, c2).getPieceType() == PieceType::PAWN && board.getTile(r1, c2).getPiece()->getTeam() != cur && prevMove[0][0] == r1 - 2 && prevMove[0][1] == c2 && prevMove[1][0] == r1 && prevMove[1][1] == c2)
                            {
                                pawn->setEnPassant(false);
                                isEnpassantMove = true;
                                return true;
                            }
                            else if (cur == Team::B && r2 == r1 + 1 && c2 == c1 + 1 && endTile.getPiece() == nullptr && board.getTile(r1, c2).getPieceType() == PieceType::PAWN && board.getTile(r1, c2).getPiece()->getTeam() != cur && prevMove[0][0] == r1 + 2 && prevMove[0][1] == c2 && prevMove[1][0] == r1 && prevMove[1][1] == c2)
                            {
                                pawn->setEnPassant(false);
                                isEnpassantMove = true;
                                return true;
                            }
                            else
                            {
                                isEnpassantMove = false;
                                return false;
                            }
                        }
                        else if (c1 == 7)
                        {
                            if (cur == Team::W && r2 == r1 - 1 && c2 == c1 - 1 && endTile.getPiece() == nullptr && board.getTile(r1, c2).getPieceType() == PieceType::PAWN && board.getTile(r1, c2).getPiece()->getTeam() != cur && prevMove[0][0] == r1 - 2 && prevMove[0][1] == c2 && prevMove[1][0] == r1 && prevMove[1][1] == c2)
                            {
                                pawn->setEnPassant(false);
                                isEnpassantMove = true;
                                return true;
                            }
                            else if (cur == Team::B && r2 == r1 + 1 && c2 == c1 - 1 && endTile.getPiece() == nullptr && board.getTile(r1, c2).getPieceType() == PieceType::PAWN && board.getTile(r1, c2).getPiece()->getTeam() != cur && prevMove[0][0] == r1 + 2 && prevMove[0][1] == c2 && prevMove[1][0] == r1 && prevMove[1][1] == c2)
                            {
                                pawn->setEnPassant(false);
                                isEnpassantMove = true;
                                return true;
                            }
                            else
                            {
                                isEnpassantMove = false;
                                return false;
                            }
                        }
                        else
                        {
                            if (cur == Team::W && r2 == r1 - 1 && c2 == c1 + 1 && endTile.getPiece() == nullptr && board.getTile(r1, c2).getPieceType() == PieceType::PAWN && board.getTile(r1, c2).getPiece()->getTeam() != cur && prevMove[0][0] == r1 - 2 && prevMove[0][1] == c2 && prevMove[1][0] == r1 && prevMove[1][1] == c2)
                            {
                                pawn->setEnPassant(false);
                                isEnpassantMove = true;
                                return true;
                            }
                            else if (cur == Team::B && r2 == r1 + 1 && c2 == c1 + 1 && endTile.getPiece() == nullptr && board.getTile(r1, c2).getPieceType() == PieceType::PAWN && board.getTile(r1, c2).getPiece()->getTeam() != cur && prevMove[0][0] == r1 + 2 && prevMove[0][1] == c2 && prevMove[1][0] == r1 && prevMove[1][1] == c2)
                            {
                                pawn->setEnPassant(false);
                                isEnpassantMove = true;
                                return true;
                            }
                            else if (cur == Team::W && r2 == r1 - 1 && c2 == c1 - 1 && endTile.getPiece() == nullptr && board.getTile(r1, c2).getPieceType() == PieceType::PAWN && board.getTile(r1, c2).getPiece()->getTeam() != cur && prevMove[0][0] == r1 - 2 && prevMove[0][1] == c2 && prevMove[1][0] == r1 && prevMove[1][1] == c2)
                            {
                                pawn->setEnPassant(false);
                                isEnpassantMove = true;
                                return true;
                            }
                            else if (cur == Team::B && r2 == r1 + 1 && c2 == c1 - 1 && endTile.getPiece() == nullptr && board.getTile(r1, c2).getPieceType() == PieceType::PAWN && board.getTile(r1, c2).getPiece()->getTeam() != cur && prevMove[0][0] == r1 + 2 && prevMove[0][1] == c2 && prevMove[1][0] == r1 && prevMove[1][1] == c2)
                            {
                                pawn->setEnPassant(false);
                                isEnpassantMove = true;
                                return true;
                            }
                            else
                            {
                                isEnpassantMove = false;
                                return false;
                            }
                        }
                    }
                    piece->setHasMovedToTrue();
                    return true;
                }

                if (!dynamic_cast<Pawn *>(piece)->getEnPassant() && piece->getTeam() == Team::W && r2 == 3)
                {
                    dynamic_cast<Pawn *>(piece)->setEnPassant(true);
                }
                else if (!dynamic_cast<Pawn *>(piece)->getEnPassant() && piece->getTeam() == Team::B && r2 == 4)
                {
                    dynamic_cast<Pawn *>(piece)->setEnPassant(true);
                }
                else
                {
                    dynamic_cast<Pawn *>(piece)->setEnPassant(false);
                }

                piece->setHasMovedToTrue();
                return true;
            }

            if (endTile.getPiece() != nullptr && endTile.getPiece()->getTeam() == cur)
            {
                return false;
            }


            if (piece->getPieceType() == PieceType::KING && r1 == r2 && (c2 == c1 + 2 || c2 == c1 - 2))
            {
                cout << "Inside Cassle" << endl;
                if (piece->getHasMoved())
                    return false;
                textdisplay = printTable();
                std::vector<std::vector<char>> textdisplay2 = textdisplay;
                if (isKingInCheck(textdisplay, cur == Team::W))
                    return false;
                if (c2 == c1 + 2)
                {
                    if (board.getTile(r1, c1 + 3).getPiece() != nullptr && board.getTile(r1, c1 + 3).getPieceType() == PieceType::ROOK && !board.getTile(r1, c1 + 3).getPiece()->getHasMoved() && board.getTile(r1, c1 + 1).getPiece() == nullptr && board.getTile(r1, c1 + 2).getPiece() == nullptr)
                    {

                        Piece *capturedPiece = endTile.getPiece();
                        startTile.checkRemove();
                        cassleTileR.checkPlace(piece);
                        // Check if the king is in check after the move
                        textdisplay = printTable();
                        bool kingInCheck = isKingInCheck(textdisplay, cur == Team::W);
                        //check if king will slide into a check position during cassle

                        // Undo the move
                        cassleTileR.checkRemove();
                        startTile.checkPlace(piece);
                        if (capturedPiece)
                        {
                            cassleTileR.checkPlace(capturedPiece);
                        }
                        textdisplay = printTable();
                        if (kingInCheck)
                        {
                            return false;
                        }

                        isCassleMove = true;
                        piece->setHasMovedToTrue();
                        board.getTile(r1, c1 + 3).getPiece()->setHasMovedToTrue();
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else if (c2 == c1 - 2)
                {
                    if (board.getTile(r1, c1 - 4).getPiece() != nullptr && board.getTile(r1, c1 - 4).getPieceType() == PieceType::ROOK && !board.getTile(r1, c1 - 4).getPiece()->getHasMoved() && board.getTile(r1, c1 - 1).getPiece() == nullptr && board.getTile(r1, c1 - 2).getPiece() == nullptr && board.getTile(r1, c1 - 3).getPiece() == nullptr)
                    {

                        Piece *capturedPiece = endTile.getPiece();
                        startTile.checkRemove();
                        cassleTileL.checkPlace(piece);
                        textdisplay = printTable();
                        // Check if the king is in check after the move
                        bool kingInCheck = isKingInCheck(textdisplay, cur == Team::W);
                        //check if king will slide into a check position during cassle
                        // Undo the move
                        cassleTileL.checkRemove();
                        startTile.checkPlace(piece);
                        if (capturedPiece)
                        {
                            cassleTileL.checkPlace(capturedPiece);
                        }
                        textdisplay = printTable();
                        if (kingInCheck)
                        {
                            return false;
                        }

                        isCassleMove = true;
                        piece->setHasMovedToTrue();
                        board.getTile(r1, c1 - 4).getPiece()->setHasMovedToTrue();
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }


            piece->setHasMovedToTrue();
            return true;
        }

        if (piece->getPieceType() == PieceType::PAWN || piece->getPieceType() == PieceType::ROOK || piece->getPieceType() == PieceType::BISHOP || piece->getPieceType() == PieceType::QUEEN)
        {
            if (isPathObstructed(r1, c1, r2, c2))
            {
                return false;
            }
        }
    }

    return false;
}

bool Game::isCheck()
{

    // get location of the king
    Tile *kingTile = nullptr;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Piece *temp = board.getTile(i, j).getPiece();

            if (temp != nullptr && temp->getPieceType() == PieceType::KING && temp->getTeam() != cur)
            {
                kingTile = &board.getTile(i, j);
                break;
            }
        }
        if (kingTile != nullptr)
        {
            break;
        }
    }

    // get list of all possible enemy moves. If one of those moves can capture the king then the king is in check
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Piece *temp = board.getTile(i, j).getPiece();
            if (temp != nullptr && temp->getTeam() == cur)
            {
                for (auto move : temp->fetchAllMoves())
                {
                    if (simpleIsValidMove(i, j, move[0], move[1]))
                    {
                        if (move[0] == kingTile->getRow() && move[1] == kingTile->getCol())
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

//check if one of your team's pieces is blocking a move
bool Game::isPathObstructed(int r1, int c1, int r2, int c2)
{
    bool isDiagonal = false;
    int rowDirection = (r2 - r1) > 0 ? 1 : (r2 - r1) < 0 ? -1
                                                         : 0;
    int colDirection = (c2 - c1) > 0 ? 1 : (c2 - c1) < 0 ? -1
                                                         : 0;

    int currentRow = r1 + rowDirection;
    int currentCol = c1 + colDirection;

    if (rowDirection != 0 && colDirection != 0)
    {
        isDiagonal = true;
    }

    while (currentRow != r2 || currentCol != c2)
    {
        if (board.getTile(currentRow, currentCol).getPiece() != nullptr)
        {
            return true;
        }
        currentRow += rowDirection;
        currentCol += colDirection;
    }

    return false;
}

//find all moves to get out of check
vector<vector<int>> Game::resolveCheckMoves()
{
    vector<vector<int>> result;

    vector<vector<char>> tempBoard = printTable();
    vector<vector<char>> tempBoard2 = tempBoard;
    bool teamFlag = cur == Team::W ? false : true;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Piece *temp = board.getTile(i, j).getPiece();
            if (temp != nullptr && temp->getTeam() != cur)
            {
                for (auto move : temp->fetchAllMoves())
                {
                    if (simpleIsValidMove(i, j, move[0], move[1]))
                    {

                        char fillChar = tempBoard[i][j];
                        tempBoard[move[0]][move[1]] = fillChar;
                        tempBoard[i][j] = ' ';


                        if (!isKingInCheck(tempBoard, teamFlag))
                        {
                            result.push_back({i, j, move[0], move[1]});
                        }

                        tempBoard = tempBoard2;
                    }
                }
            }
        }
    }

    return result;
}

vector<vector<int>> Game::allPossibleMoves()
{
    vector<vector<int>> result;

    vector<vector<char>> tempBoard = printTable();
    vector<vector<char>> tempBoard2 = tempBoard;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Piece *temp = board.getTile(i, j).getPiece();
            if (temp != nullptr && temp->getTeam() != cur)
            {
                for (auto move : temp->fetchAllMoves())
                {
                    if (simpleIsValidMove(i, j, move[0], move[1]))
                    {

                        char fillChar = tempBoard[i][j];
                        tempBoard[move[0]][move[1]] = fillChar;
                        tempBoard[i][j] = ' ';

                        if (!isKingInCheck(tempBoard, temp->getTeam() == Team::W))
                        {
                            result.push_back({i, j, move[0], move[1]});
                        }

                        tempBoard = tempBoard2;
                    }
                }
            }
        }
    }

    return result;
}

// create a temporary copy of the board using chars
vector<vector<char>> Game::printTable()
{
    vector<vector<char>> tempBoard = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Piece *temp = board.getTile(i, j).getPiece();
            if (temp != nullptr)
            {
                if (temp->getPieceType() == PieceType::KING)
                {
                    if (temp->getTeam() == Team::W)
                    {
                        tempBoard[i][j] = 'K';
                    }
                    else
                    {
                        tempBoard[i][j] = 'k';
                    }
                }
                else if (temp->getPieceType() == PieceType::QUEEN)
                {
                    if (temp->getTeam() == Team::W)
                    {
                        tempBoard[i][j] = 'Q';
                    }
                    else
                    {
                        tempBoard[i][j] = 'q';
                    }
                }
                else if (temp->getPieceType() == PieceType::BISHOP)
                {
                    if (temp->getTeam() == Team::W)
                    {
                        tempBoard[i][j] = 'B';
                    }
                    else
                    {
                        tempBoard[i][j] = 'b';
                    }
                }
                else if (temp->getPieceType() == PieceType::PAWN)
                {
                    if (temp->getTeam() == Team::W)
                    {
                        tempBoard[i][j] = 'P';
                    }
                    else
                    {
                        tempBoard[i][j] = 'p';
                    }
                }
                else if (temp->getPieceType() == PieceType::KNIGHT)
                {
                    if (temp->getTeam() == Team::W)
                    {
                        tempBoard[i][j] = 'N';
                    }
                    else
                    {
                        tempBoard[i][j] = 'n';
                    }
                }
                else if (temp->getPieceType() == PieceType::ROOK)
                {
                    if (temp->getTeam() == Team::W)
                    {
                        tempBoard[i][j] = 'R';
                    }
                    else
                    {
                        tempBoard[i][j] = 'r';
                    }
                }
            }
        }
    }

    return tempBoard;
}

// check if in bounds
bool Game::isValid(int x, int y)
{
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

// function to find the king's position on the board
pair<int, int> findKing(const vector<vector<char>> &board, bool isWhite)
{
    char king = isWhite ? 'K' : 'k';
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board[i][j] == king)
            {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // shouldn't ever happen, but needed for compilation
}

// Function to check if a position is attacked by a pawn
bool Game::isAttackedByPawn(const vector<vector<char>> &board, int x, int y, bool isWhite)
{
    if (isWhite)
    {
        return (isValid(x - 1, y - 1) && board[x - 1][y - 1] == 'p') ||
               (isValid(x - 1, y + 1) && board[x - 1][y + 1] == 'p');
    }
    else
    {
        return (isValid(x + 1, y - 1) && board[x + 1][y - 1] == 'P') ||
               (isValid(x + 1, y + 1) && board[x + 1][y + 1] == 'P');
    }
}

// Function to check if a position is attacked by a knight
bool Game::isAttackedByKnight(const vector<vector<char>> &board, int x, int y, bool isWhite)
{
    vector<pair<int, int>> knightMoves = {
        {x + 2, y + 1}, {x + 2, y - 1}, {x - 2, y + 1}, {x - 2, y - 1}, {x + 1, y + 2}, {x + 1, y - 2}, {x - 1, y + 2}, {x - 1, y - 2}};
    char knight = isWhite ? 'n' : 'N';
    for (auto move : knightMoves)
    {
        if (isValid(move.first, move.second) && board[move.first][move.second] == knight)
        {
            return true;
        }
    }
    return false;
}

// Function to check if a position is attacked by a sliding piece (bishop, rook, or queen)
bool Game::isAttackedBySlidingPiece(const vector<vector<char>> &board, int x, int y, bool isWhite, const vector<pair<int, int>> &directions, char piece1, char piece2)
{
    for (auto dir : directions)
    {
        int dx = dir.first;
        int dy = dir.second;
        int nx = x + dx;
        int ny = y + dy;
        piece1 = isWhite ? tolower(piece1) : toupper(piece1);
        piece2 = isWhite ? tolower(piece2) : toupper(piece2);
        while (isValid(nx, ny))
        {
            if (board[nx][ny] != ' ')
            {
                if ((board[nx][ny] == piece1 || board[nx][ny] == piece2))
                {
                    return true;
                }
                break;
            }
            nx += dx;
            ny += dy;
        }
    }
    return false;
}

// Main function to check if the king is in check
bool Game::isKingInCheck(const vector<vector<char>> &board, bool isWhite)
{
    pair<int, int> kingPos = findKing(board, isWhite);
    int kingX = kingPos.first;
    int kingY = kingPos.second;

    // Directions for rooks and queens
    vector<pair<int, int>> rookDirections = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    // Directions for bishops and queens
    vector<pair<int, int>> bishopDirections = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    return isAttackedByPawn(board, kingX, kingY, isWhite) ||
           isAttackedByKnight(board, kingX, kingY, isWhite) ||
           isAttackedBySlidingPiece(board, kingX, kingY, isWhite, rookDirections, isWhite ? 'r' : 'R', isWhite ? 'q' : 'Q') ||
           isAttackedBySlidingPiece(board, kingX, kingY, isWhite, bishopDirections, isWhite ? 'b' : 'B', isWhite ? 'q' : 'Q');
}
