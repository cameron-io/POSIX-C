CC = gcc
CFLAGS = -O -DNORMALUNIX -DLINUX -I include
LDFLAGS =
LIBS = -lm

BUILD_DIR = .out
OBJ = $(BUILD_DIR)/obj
BIN = $(BUILD_DIR)/bin

SOURCE_DIR = src
SOURCES = $(shell find $(SOURCE_DIR) -name '*.c' -type f -printf "%f " | xargs)
BINARIES = $(addprefix $(BIN)/,$(SOURCES:%.c=%.out))

CLR = '\033[1;32m'
NC = '\033[0m'

.PHONY: compile run clean

compile: $(BINARIES)
	@echo compilation complete.

run: compile
	@echo -e ${CLR}Running tests...${NC} $(TEST)
	@./$(BIN)/$(TEST).out

$(BIN)/%.out: $(OBJ)/%.o
	@echo "> linking $@..."
	@mkdir -p $(BIN)
	@$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ $(LIBS)

$(OBJ)/%.o: $(SOURCE_DIR)/%.c
	@echo -e ${CLR}compiling $<...${NC}
	@mkdir -p $(OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
