CC = gcc
CFLAGS = -O -DNORMALUNIX -DLINUX -I include
LDFLAGS =
LIBS = -lm

BUILD_DIR = .out
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

SOURCE_DIR = src
SOURCE_DIR_PATHS = $(shell echo $(SOURCE_DIR)/*)
RESOURCES = $(shell for i in $(SOURCE_DIR_PATHS); do echo $${i#"$(SOURCE_DIR)/"}; done)

SOURCE_PATHS = $(shell find $(SOURCE_DIR) -type f)
SOURCE_FILES = $(shell for i in $(SOURCE_PATHS); do echo $${i#"$(SOURCE_DIR)/"}; done)

BINARIES = $(addprefix $(BIN_DIR)/, $(SOURCE_FILES:%.c=%.out))

CLR = '\033[1;32m'
NC = '\033[0m'

.PHONY: compile run clean

compile: $(BIN_DIR) $(OBJ_DIR) $(BINARIES)
	@echo compilation complete.

run: compile
	@echo -e ${CLR}Running tests...${NC} $(TEST)
	@./$(BIN_DIR)/$(TEST).out

$(BIN_DIR)/%.out: $(OBJ_DIR)/%.o
	@echo "> linking..."
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_DIR)/$(<F) -o $(BIN_DIR)/$(@F) $(LIBS)

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c
	@echo -e ${CLR}compiling $<...${NC}
	@$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)/$(@F)

$(BIN_DIR):
	@mkdir -p $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)
	@echo "removed build directory"
