# Display Makefile

# Source files
SRC = src/graphic.cc src/text.cc src/XWindow.cc

# Object files
OBJ = $(SRC:.cc=.o)

# Compiler and flags
CXX = g++
CXXFLAGS = -Iinclude

all: $(OBJ)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
