BIN_DIR  = ../bin
OBJS_DIR = ../obj
INCL_DIR = ../include
COMM_INCL_DIR = ../../include

OBJS	 = $(OBJS_DIR)/main.o $(OBJS_DIR)/captain.o $(OBJS_DIR)/logger.o $(OBJS_DIR)/log_stream.o
SOURCE	 = main.cpp Captain.cpp logger.cpp log_stream.cpp
HEADER	 = $(INCL_DIR)/Captain.h $(INCL_DIR)/CleaningCrew.h $(INCL_DIR)/EngineCrew.h $(INCL_DIR)/zotikos.h $(INCL_DIR)/logger.h $(INCL_DIR)/log_stream.h $(INCL_DIR)/log_states.h $(INCL_DIR)/timeutil.h $(COMM_INCL_DIR)/common.h
OUT	     = $(BIN_DIR)/main
CXX	     = g++
CXXFLAGS = -O2 -std=c++20 -Wall -Wextra -pedantic
LDLIBS	 = -lpthread
CPPFLAGS = -I$(INCL_DIR) -I$(COMM_INCL_DIR)

all: $(OBJS)
	$(CXX) $(OBJS) -o $(OUT) $(LDLIBS)

$(OBJS_DIR)/main.o: main.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJS_DIR)/captain.o: Captain.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJS_DIR)/logger.o: logger.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJS_DIR)/log_stream.o: log_stream.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OUT)