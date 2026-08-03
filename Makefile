CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = $(wildcard *.c)
BIN = hanoi

.PHONY: all run clean

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

run: all
	./$(BIN)

clean:
	rm -f $(BIN)