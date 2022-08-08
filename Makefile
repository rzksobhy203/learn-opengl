CC = clang
CXX = clang++
CFLAGS  = -Wall -Wextra -pedantic -std=c++17 -ggdb

SRC = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp) $(wildcard src/**/**/*.cpp)
OBJ = $(SRC:.cpp=.o)
BIN = bin

.PHONY: all clean

all: $(BIN) $(BIN)/output

$(BIN):
	mkdir -p ./$(BIN)

$(BIN)/output: $(OBJ)
	$(CXX) -o $(@) $(^) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -o $(@) -c $(<)

run: all
	./$(BIN)/output

clean:
	rm -rf $(BIN) $(OBJ)
