.PHONY: clean all COMMONDDS_HOME

CC = g++
CFLAGS = -Iinclude -I$(COMMONDDS_HOME)/include -Isrc/idl_opendds

SRCS = src/Message_opendds.cpp
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

all: pub sub

COMMONDDS_HOME:
ifndef COMMONDDS_HOME
    COMMONDDS_HOME = ../..
endif

pub: $(OBJS) obj/pub.o
	$(CC) $(CFLAGS) -o $@ $^ $(COMMONDDS_HOME)/libdds.a

sub: $(OBJS) obj/sub.o
	$(CC) $(CFLAGS) -o $@ $^ $(COMMONDDS_HOME)/libdds.a

obj/%.o: src/%.cpp
	-mkdir -p obj
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf obj
	rm -f pub sub
