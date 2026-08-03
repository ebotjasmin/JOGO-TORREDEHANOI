CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
SRC = $(wildcard src/*.c)
BIN = hanoi

.PHONY: all run clean

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

run: all
	./$(BIN)

clean:
	rm -f $(BIN)