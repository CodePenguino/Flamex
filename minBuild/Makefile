# Quick note, please install mingw for this!

# Change this to you compiler of choice (I chose g++)
CC = g++
SRC = $(wildcard ../src/*.cpp) $(wildcard ../src/*/*.cpp) $(wildcard ../src/*/*/*.cpp) $(wildcard ../src/*/*/*/*.cpp)
LIBS = -lmingw32 -lglfw3dll -lopengl32
DIRS = -I../include/ -L../lib/

all: $(SRC)
	$(CC) $(SRC) $(DIRS) $(LIBS)
