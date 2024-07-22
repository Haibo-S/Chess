# Root Makefile

SUBDIRS = Board Display Pieces Player

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -f main

# Link all object files to create the main executable
main: main.o Board/src/board.o Board/src/tile.o Display/src/graphic.o Display/src/observer.o Display/src/text.o Display/src/XWindow.o Pieces/src/bishop.o Pieces/src/king.o Pieces/src/knight.o Pieces/src/pawn.o Pieces/src/piece.o Pieces/src/queen.o Pieces/src/rook.o Player/src/human.o Player/src/level1.o Player/src/level2.o Player/src/level3.o Player/src/level4.o Player/src/player.o
	g++ -o main main.o Board/src/board.o Board/src/tile.o Display/src/graphic.o Display/src/observer.o Display/src/text.o Display/src/XWindow.o Pieces/src/bishop.o Pieces/src/king.o Pieces/src/knight.o Pieces/src/pawn.o Pieces/src/piece.o Pieces/src/queen.o Pieces/src/rook.o Player/src/human.o Player/src/level1.o Player/src/level2.o Player/src/level3.o Player/src/level4.o Player/src/player.o

main.o: main.cc
	g++ -c main.cc

.PHONY: all clean $(SUBDIRS)
