CPPFLAGS=-I ../../src/ $(wildcard ../../src/*.cpp) $(wildcard ../../src/**/*.cpp)
CC=g++
LDLIBS=-ljsoncpp -lcurl

all: main

clean:
	rm -f *.o main.out

.PHONY: all clean