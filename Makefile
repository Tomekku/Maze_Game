ALL_SRCS := $(wildcard src/*.c)
SRCS     := $(filter-out src/functions.c, $(ALL_SRCS))

start:
	gcc  $(SRCS) -o bin/GAME -std=c99  -I /usr/include/SDL2 -lSDL2 -lSDL2_ttf -lSDL2_image -g