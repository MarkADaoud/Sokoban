CC = g++
CFLAGS = --std=c++20 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# Your .hpp files
DEPS = Sokoban.hpp
# Your compiled .o files
OBJECTS = Sokoban.o 
# The name of your program
PROGRAM = Sokoban

.PHONY: all clean lint

all: $(PROGRAM) Sokoban.a test

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

Sokoban.a: Sokoban.o
	ar rcs Sokoban.a Sokoban.o

test: test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o test test.o $(OBJECTS) $(LIB)

clean:
	rm *.o $(PROGRAM) Sokoban.a test

lint:
	cpplint *.cpp *.hpp



