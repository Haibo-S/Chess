# Player/Makefile

SRC = src/human.cc src/level1.cc src/level2.cc src/level3.cc src/level4.cc src/player.cc
OBJ = $(SRC:.cc=.o)
CXXFLAGS = -Iinclude -g

all: $(OBJ)

%.o: %.cc
	g++ $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
