.PHONY: clean all COMMONDDS_HOME

CC = g++
CFLAGS = -Iinclude -I$(COMMONDDS_HOME)/include

SRCS = src/Message.cpp
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

all: client

COMMONDDS_HOME:
ifndef COMMONDDS_HOME
    COMMONDDS_HOME = ../..
endif

client: $(OBJS) obj/client.o
	$(CC) $(CFLAGS) -o $@ $^ $(COMMONDDS_HOME)/libdds.a

obj/%.o: src/%.cpp
	-mkdir -p obj
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf obj
	rm -f client server
