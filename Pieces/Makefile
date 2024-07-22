# Pieces/Makefile

SRC = src/bishop.cc src/king.cc src/knight.cc src/pawn.cc src/piece.cc src/queen.cc src/rook.cc
OBJ = $(SRC:.cc=.o)
CXXFLAGS = -Iinclude

all: $(OBJ)

%.o: %.cc
	g++ $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
