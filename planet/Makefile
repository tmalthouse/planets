CC=gcc
CFLAGS=-O3 -std="c99"
LDFLAGS=-lSDL2 -lSDL2_ttf -lSDL2_image -lm

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
GRAPHICS_SRCS=$(wildcard graphics/*.c)
GRAPHICS_OBJS=$(GRAPHICS_SRCS:.c=.o)

OUTPUT=planet

all: $(OBJS)
	cd graphics; make
	$(CC) $(OBJS) $(GRAPHICS_OBJS) $(CFLAGS) -o$(OUTPUT) $(LDFLAGS)

clean:
	rm -f *.o *.gch graphics/*.o graphics/*.gch
