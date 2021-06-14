CC=gcc
CXX=g++
RM=rm -f

TARGET=main

INCLUDES=-I./include -I.
LDFLAGS=
LDLIBS=-lpthread -fopenmp

CXXFLAGS=-std=c++17 -Wall -O2 -fopenmp

DIR_OBJ=objs

SRCS=$(wildcard *.cc)

OBJS=$(patsubst %.cc,$(DIR_OBJ)/%.o,$(SRCS))


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDLIBS) $(LDFLAGS) 

$(DIR_OBJ)/%.o: %.cc
	@mkdir -p $(DIR_OBJ)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(INCLUDES)

clean:
	@$(RM) $(OBJS)
	@$(RM) *~ core

distclean: clean
	@$(RM) $(TARGET)
	@$(RM) -r $(DIR_OBJ)

.PHONY: all clean distclean
	
