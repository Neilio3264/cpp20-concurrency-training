BIN_DIR  = ../bin
OBJS_DIR = ../obj
INCL_DIR = ../include
COMM_INCL_DIR = ../../../include

OBJS	 = $(OBJS_DIR)/main.o
SOURCE	 = main.cpp
HEADER	 = $(INCL_DIR)/bus.h $(COMM_INCL_DIR)/common.h
OUT	     = $(BIN_DIR)/main
CXX	     = g++
CXXFLAGS = -O2 -std=c++20 -Wall -Wextra -pedantic
LDLIBS	 = -lpthread
CPPFLAGS = -I$(INCL_DIR) -I$(COMM_INCL_DIR)

all: $(OBJS)
	$(CXX) $(OBJS) -o $(OUT) $(LDLIBS)

$(OBJS_DIR)/main.o: main.cpp $(HEADER)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OUT)