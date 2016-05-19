CC=gcc
CFLAGS=-O3
LDFLAGS=-llibSDL2 -llibSDL2_ttf -llibSDL2_img

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

OUTPUT=planet

all: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o$(OUTPUT) $(LDFLAGS)
