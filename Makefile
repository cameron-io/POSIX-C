CC = gcc
CFLAGS = -O -DNORMALUNIX -DLINUX -I include
LDFLAGS =
LIBS = -lm

BUILD_DIR = .out
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

SOURCE_DIR = src
SOURCES = $(shell find $(SOURCE_DIR) -name '*.c' -type f -printf "%f " | xargs)
BINARIES = $(addprefix $(BIN_DIR)/,$(SOURCES:%.c=%.out))

CLR = '\033[1;32m'
NC = '\033[0m'

.PHONY: compile run clean

compile: $(BINARIES)
	@echo compilation complete.

run: compile
	@echo -e ${CLR}Running tests...${NC} $(TEST)
	@./$(BIN_DIR)/$(TEST).out

$(BIN_DIR)/%.out: $(OBJ_DIR)/%.o
	@echo "> linking $@..."
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ $(LIBS)

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c
	@echo -e ${CLR}compiling $<...${NC}
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
