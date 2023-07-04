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
	@echo compilation complete.

%.out: %.o
	@echo "  > linking $@..."
	@mkdir -p $(BIN)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ)/$< -o $(BIN)/$@ $(LIBS)

%.o: $(SRC)/%.c
	@echo - compiling $<...
	@mkdir -p $(OBJ)
	@$(CC) $(CFLAGS) -c $< -o $(OBJ)/$@

clean:
	rm -rf $(BUILD)
