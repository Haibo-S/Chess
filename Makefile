# Root Makefile

SUBDIRS = Board Display Pieces

all: $(SUBDIRS) main

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -f main main.o

# Link all object files to create the main executable
main: main.o Board/src/board.o Board/src/tile.o Board/src/subject.o Display/src/graphic.o Display/src/text.o Display/src/XWindow.o Pieces/src/bishop.o Pieces/src/king.o Pieces/src/knight.o Pieces/src/pawn.o Pieces/src/piece.o Pieces/src/queen.o Pieces/src/rook.o 
	g++ -o main main.o Board/src/board.o Board/src/tile.o Board/src/subject.o Display/src/graphic.o Display/src/text.o Display/src/XWindow.o Pieces/src/bishop.o Pieces/src/king.o Pieces/src/knight.o Pieces/src/pawn.o Pieces/src/piece.o Pieces/src/queen.o Pieces/src/rook.o -lX11

main.o: main.cc
	g++ -IBoard/include -IDisplay/include -IPieces/include -c main.cc

Board/src/subject.o: Board/src/subject.cc
	g++ -IBoard/include -c Board/src/subject.cc -o Board/src/subject.o

.PHONY: all clean $(SUBDIRS)
