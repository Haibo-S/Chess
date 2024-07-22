# Board/Makefile

SRC = src/board.cc src/tile.cc
OBJ = $(SRC:.cc=.o)
CXXFLAGS = -Iinclude

all: $(OBJ)

%.o: %.cc
	g++ $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
