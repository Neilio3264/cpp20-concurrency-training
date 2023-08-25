BIN_DIR  = ../bin
OBJS_DIR = ../obj
INCL_DIR = ../include

OBJS	= $(OBJS_DIR)/main.o
SOURCE	= main.cpp
HEADER	= $(INCL_DIR)/thread.h
OUT	    = $(BIN_DIR)/main
CC	    = g++
FLAGS	= -O2 -c -std=c++20 -Wall -Wextra -pedantic
LFLAGS	= -lpthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

$(OBJS_DIR)/main.o: main.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OUT)