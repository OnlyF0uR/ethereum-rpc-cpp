CPPFLAGS=-I ../src ../src/wrapper.cc ../src/endpoints/getter.cc  ../src/endpoints/sender.cc
CC=g++
LDLIBS=-ljsoncpp -lcurl

all: main

clean:
	rm -f *.o main.out

.PHONY: all clean