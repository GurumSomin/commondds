.PHONY: clean all

CC = g++
CFLAGS = -Iinclude
AR = ar

SRCS = src/jsoncpp.cpp src/dcps.cpp src/connext.cpp
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

all: libdds.a

libdds.a: $(OBJS)
	$(AR) rvs $@ $^

test: $(OBJS) obj/test.o
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.cpp
	-mkdir -p obj
	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	rm -rf obj
	rm -f libdds.a
