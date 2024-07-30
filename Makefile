SUBDIRS = Board Display Pieces Player

all: $(SUBDIRS) main

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -f main main.o game.o

# Link all object files to create the main executable
main: main.o game.o Board/src/board.o Board/src/tile.o Board/src/subject.o Display/src/graphic.o Display/src/text.o Display/src/XWindow.o Pieces/src/bishop.o Pieces/src/king.o Pieces/src/knight.o Pieces/src/pawn.o Pieces/src/piece.o Pieces/src/queen.o Pieces/src/rook.o Player/src/human.o Player/src/level1.o Player/src/level2.o Player/src/level3.o Player/src/level4.o Player/src/player.o
	g++ -o main main.o game.o Board/src/board.o Board/src/tile.o Board/src/subject.o Display/src/graphic.o Display/src/text.o Display/src/XWindow.o Pieces/src/bishop.o Pieces/src/king.o Pieces/src/knight.o Pieces/src/pawn.o Pieces/src/piece.o Pieces/src/queen.o Pieces/src/rook.o Player/src/human.o Player/src/level1.o Player/src/level2.o Player/src/level3.o Player/src/level4.o Player/src/level5.o Player/src/player.o -lX11

game.o: game.cc
	g++ -g -IBoard/include -IDisplay/include -IPieces/include -IPlayer/include -c game.cc

main.o: main.cc
	g++ -g -IBoard/include -IDisplay/include -IPieces/include -IPlayer/include -c main.cc

Board/src/subject.o: Board/src/subject.cc
	g++ -IBoard/include -c Board/src/subject.cc -o Board/src/subject.o

.PHONY: all clean $(SUBDIRS)
