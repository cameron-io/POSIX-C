CC=gcc
CFLAGS=-O -DNORMALUNIX -DLINUX
LDFLAGS=
LIBS=-lm

SRC=src

BUILD=.out
OBJ=$(BUILD)/obj
BIN=$(BUILD)/bin

BINARIES = HashTable.out Search.out Sort.out
OBJECTS = HashTable.o Search.o Sort.o

.PHONY: all compile run clean

compile: $(BINARIES)
	@echo make complete.

%.out: $(OBJECTS)
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ)/$< -o $(BIN)/$@ $(LIBS)

# Rule
%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $(OBJ)/$@

clean:
	rm -rf $(BUILD)
