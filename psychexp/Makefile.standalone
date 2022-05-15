# Makefile to create the static library 'libpsychexp.a'
# Time-stamp: <2022-05-15 11:20:04 christophe@pallier.org>

CC=gcc
CFLAGS=-g -O2
INCLUDES=-I/usr/include/SDL2
LDLIBS=-lSDL2

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

$(obj): $(SRC)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

libpsychexp.a: psychexp.o
	ar rcs $@ $^

