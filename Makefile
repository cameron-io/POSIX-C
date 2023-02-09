CC=gcc
CFLAGS=-O -DNORMALUNIX -DLINUX
LDFLAGS=
LIBS=-lm

SRC=src

BUILD=.out
OBJ=$(BUILD)/obj
BIN=$(BUILD)/bin

SOURCES = HashTable.out Search.out Sort.out

.PHONY: compile run clean

compile: $(SOURCES)
	@echo make complete.

%.out: %.o
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ)/$< -o $(BIN)/$@ $(LIBS)

# Rule
%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $(OBJ)/$@

clean:
	rm -rf $(BUILD)
