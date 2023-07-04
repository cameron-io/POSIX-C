CC = gcc
CFLAGS = -O -DNORMALUNIX -DLINUX
LDFLAGS =
LIBS = -lm

SRC = src

BUILD =.out
OBJ = $(BUILD)/obj
BIN = $(BUILD)/bin

SOURCES = HashTable.out Search.out Sort.out Stack.out

CLR = '\033[1;32m'
NC = '\033[0m'

.PHONY: compile run clean

compile: $(SOURCES)
	@echo compilation complete.

run: compile
	@echo -e ${CLR}Running tests...${NC} $(TEST)
	@./$(BIN)/$(TEST).out

%.out: %.o
	@echo "> linking $@..."
	@mkdir -p $(BIN)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ)/$< -o $(BIN)/$@ $(LIBS)

%.o: $(SRC)/%.c
	@echo -e ${CLR}compiling $<...${NC}
	@mkdir -p $(OBJ)
	@$(CC) $(CFLAGS) -c $< -o $(OBJ)/$@

clean:
	rm -rf $(BUILD)
