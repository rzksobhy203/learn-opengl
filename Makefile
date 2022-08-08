UNAME_S = $(shell uname -s)

CC = clang
CXX = clang++
CFLAGS  = -Wall -Wextra -pedantic -std=c++17 -ggdb
CFLAGS += -Ilib/glfw/include/ -Ilib/glad/include/
LDFLAGS = lib/glad/src/glad.o lib/glfw/src/libglfw3.a

ifeq ($(UNAME_S), Linux)
	LDFLAGS += -lGLU -lGL -ldl -lpthread
endif

SRC = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp) $(wildcard src/**/**/*.cpp) $(wildcard src/**/**/**/*.cpp)
OBJ = $(SRC:.cpp=.o)
BIN = bin

.PHONY: all clean

all: $(BIN) libs $(BIN)/output

$(BIN):
	mkdir -p ./$(BIN)

libs: lib/glad/src/glad.o lib/glfw/src/libglfw3.a

lib/glad/src/glad.o: lib/glad/src/glad.c
	cd lib/glad && $(CC) -o src/glad.o -Iinclude -c src/glad.c

lib/glfw/src/libglfw3.a:
	cd lib/glfw && cmake . && make

$(BIN)/output: $(OBJ)
	$(CXX) -o $(@) $(^) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -o $(@) -c $(<)

run: all
	./$(BIN)/output

clean:
	rm -rf $(BIN) $(OBJ)
