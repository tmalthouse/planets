CC=gcc
CFLAGS=-O0 -std="c99"
LDFLAGS=-lSDL2 -lSDL2_ttf -lSDL2_image -lm

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

GRAPHICS_OBJS=graphics/game.o graphics/message.o graphics/planet_sprite.o graphics/texture.o graphics/timer.o graphics/window.o

OUTPUT=planet

all: $(OBJS)
	cd graphics; make
	$(CC) $(OBJS) $(GRAPHICS_OBJS) $(CFLAGS) -o$(OUTPUT) $(LDFLAGS)

clean:
	rm -f *.o graphics/*.o
