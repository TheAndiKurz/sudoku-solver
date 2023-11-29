# Variables
CC = g++
CFLAGS = -Wall -Wextra -g
SRC = $(shell find src -name *.cpp)
OBJ = $(SRC:src/%.cpp=target/obj/%.o)
EXEC = target/$(shell basename `pwd`)

# Rules
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

target/obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -fr target

run: all
	./$(EXEC) sudoku
