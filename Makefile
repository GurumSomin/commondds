.PHONY: clean all

CC = g++
CFLAGS = -Iinclude

SRCS = src/dcps.cpp
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

test: $(OBJS) obj/test.o
	$(CC) $(CFLAGS) -o $@ $^

obj:
	mkdir -p $@

obj/%.o: src/%.cpp obj
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf obj
