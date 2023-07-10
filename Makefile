CC = gcc
CFLAGS = -O -DNORMALUNIX -DLINUX -I include
LDFLAGS = -pthread
LIBS = -lm

BUILD_DIR = .out
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

SOURCE_DIR = src
SOURCE_FILES = $(shell find $(SOURCE_DIR) -type f)
SOURCE_PATH = $(shell for i in $(SOURCE_FILES); do echo $${i#"$(SOURCE_DIR)/"}; done)
BIN = $(addprefix $(BIN_DIR)/, $(SOURCE_PATH:%.c=%.out))

CLR = '\033[1;32m'
NC = '\033[0m'

.PHONY: compile run clean

compile: $(BIN_DIR) $(OBJ_DIR) $(BIN)
	@echo compilation complete.

run: compile
	@echo -e ${CLR}Running tests...${NC} $(TEST)
	@./$(BIN_DIR)/$(TEST).out

$(BIN_DIR)/%.out: $(OBJ_DIR)/%.o
	@echo "> linking..."
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ $(LIBS)

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c
	@echo -e ${CLR}compiling $<...${NC}
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	@mkdir -p $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)
	@echo "removed build directory"
