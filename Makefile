CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
BUILD_DIR = build

.DEFAULT_GOAL := all

# Source directories
SRC_DIRS = src src/sorting src/searching src/trees src/graphs src/data_structures

# Find all source files (excluding tests and examples)
SRCS = $(shell find src -name '*.c')
OBJS = $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRCS))

TEST_SRCS = $(shell find tests -name '*.c')
TEST_BINS = $(patsubst tests/%.c,$(BUILD_DIR)/test_%,$(TEST_SRCS))


# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/sorting
	mkdir -p $(BUILD_DIR)/searching
	mkdir -p $(BUILD_DIR)/trees
	mkdir -p $(BUILD_DIR)/graphs
	mkdir -p $(BUILD_DIR)/data_structures

# Compile object files
$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Common object (if you have src/common.c)
$(BUILD_DIR)/common.o: src/common.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build individual test executables
$(BUILD_DIR)/test_%: tests/%.c $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Run a specific test
.PHONY: test
test: $(BUILD_DIR)/test_$(TEST)
	./$(BUILD_DIR)/test_$(TEST)

$(BUILD_DIR)/test_sorting: tests/test_sorting.c $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Build examples
example_insertion_sort_demo: $(BUILD_DIR)/example_insertion_sort_demo
	./$(BUILD_DIR)/example_insertion_sort_demo

$(BUILD_DIR)/example_insertion_sort_demo: examples/insertion_sort_demo.c $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Generic pattern for any example
example_%: $(BUILD_DIR)/example_%
	./$(BUILD_DIR)/example_$*

$(BUILD_DIR)/example_%: examples/%.c $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Clean build artifacts
.PHONY: clean test_sorting
clean:
	rm -rf $(BUILD_DIR)

# Help command
help:
	@echo "Available targets:"
	@echo "  make test_sorting              - Build and run sorting tests"
	@echo "  make example_insertion_sort_demo - Build and run insertion sort demo"
	@echo "  make clean                     - Remove build artifacts"

compile_commands.json:
	bear -- make clean all

all: $(BUILD_DIR)
	@echo "Project built"
