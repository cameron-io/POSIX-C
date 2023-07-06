CC = gcc
CFLAGS = -O -DNORMALUNIX -DLINUX -I include
LDFLAGS =
LIBS = -lm

BUILD_DIR = .out
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

SRC_DIR = src
SRC_FILES = $(shell find $(SRC_DIR) -name '*.c' -type f -printf "%f\n")
BINARIES = $(addprefix $(BIN_DIR)/,$(SRC_FILES:%.c=%.out))

CLR = '\033[1;32m'
NC = '\033[0m'

.PHONY: compile run clean

compile: $(BINARIES)
	@rm -rf $(OBJ_DIR)
	@echo compilation complete.

run: compile
	@echo -e ${CLR}Running tests...${NC} $(TEST)
	@./$(BIN_DIR)/$(TEST).out

$(BIN_DIR)/%.out: $(OBJ_DIR)/%.o
	@echo "> linking..."
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo -e ${CLR}compiling $<...${NC}
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)
	@echo "removed build directory"
