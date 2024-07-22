# Display/Makefile

SRC = src/graphic.cc src/observer.cc src/text.cc src/XWindow.cc
OBJ = $(SRC:.cc=.o)
CXXFLAGS = -Iinclude

all: $(OBJ)

%.o: %.cc
	g++ $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
