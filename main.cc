#include <iostream>
#include "./Board/include/tile.h"
#include "./Board/include/subject.h"
#include "./Board/include/board.h"
#include "./Display/include/text.h"
#include "./Display/include/graphic.h"
#include "./Display/include/observer.h"
#include "./Pieces/include/piece.h"
#include "./Pieces/include/bishop.h"
#include "./Pieces/include/rook.h"
#include "./Pieces/include/queen.h"
#include "./Pieces/include/king.h"
#include "./Pieces/include/pawn.h"
#include "./Pieces/include/knight.h"
#include "game.h"

using namespace std;

int main(){



    Game g;
    g.start();
    
    g.printScore();
    return 0;
}

