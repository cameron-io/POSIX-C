SOURCE_DIR = lib tests
BIN_DIR = .bin
BUILD_DIR = .build

.PHONY: compile
compile: $(SOURCE_DIR)
	cmake -S. -B$(BUILD_DIR)
	cmake --build ./$(BUILD_DIR)

.PHONY: test
test: compile
	ctest --test-dir ./$(BUILD_DIR)

clean:
	rm -rf ./$(BUILD_DIR) ./$(BIN_DIR)
