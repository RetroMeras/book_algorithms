CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -Iinclude/test_utils
BUILD_DIR = build
TEST_DIR = tests
TEST_UTILS_DIR = $(TEST_DIR)/test_utils
INCLUDE_TEST_UTILS_DIR = include/test_utils

# Source files
SRCS = $(shell find src -name '*.c')
OBJS = $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Test utility files (these are in tests/test_utils/)
# Exclude performance.c since it's a standalone program
TEST_UTILS_SRCS = $(filter-out $(TEST_UTILS_DIR)/performance.c, $(wildcard $(TEST_UTILS_DIR)/*.c))
TEST_UTILS_OBJS = $(patsubst $(TEST_UTILS_DIR)/%.c,$(BUILD_DIR)/test_utils/%.o,$(TEST_UTILS_SRCS))

# Individual test files (in tests/ directory)
INDIVIDUAL_TEST_SRCS = $(filter-out $(TEST_UTILS_DIR)/%, $(wildcard $(TEST_DIR)/*.c))
INDIVIDUAL_TEST_BINS = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/test_%,$(INDIVIDUAL_TEST_SRCS))

# Main test programs
ALL_TESTS = $(BUILD_DIR)/test_sorting $(BUILD_DIR)/performance

.PHONY: all clean help test test_all test_% perf performance benchmark memtest perf-quick

# Create build directory structure
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/sorting
	mkdir -p $(BUILD_DIR)/search
	mkdir -p $(BUILD_DIR)/trees
	mkdir -p $(BUILD_DIR)/graphs
	mkdir -p $(BUILD_DIR)/data_structures
	mkdir -p $(BUILD_DIR)/test_utils
	mkdir -p $(BUILD_DIR)/other

# Compile source files
$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test utility files (excluding performance.c)
$(BUILD_DIR)/test_utils/%.o: $(TEST_UTILS_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build individual test executables
$(BUILD_DIR)/test_%: $(TEST_DIR)/%.c $(TEST_UTILS_OBJS) $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Build comprehensive test suite
$(BUILD_DIR)/test_sorting: tests/test_sorting.c $(TEST_UTILS_OBJS) $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Build performance test executable - needs test_utils functions
$(BUILD_DIR)/performance: tests/test_utils/performance.c $(TEST_UTILS_OBJS) $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< $(TEST_UTILS_OBJS) $(OBJS) -o $@ -lm

# Run specific test
test_%: $(BUILD_DIR)/test_%
	@echo "🧪 Running $@..."
	./$<

# Run all individual tests
test_all: $(INDIVIDUAL_TEST_BINS)
	@echo "🔍 Running all individual tests..."
	@for test in $(INDIVIDUAL_TEST_BINS); do \
		echo "\n--- Running $$(basename $$test) ---"; \
		$$test; \
	done
	@echo "\n✅ All individual tests completed!"

# Run comprehensive test suite
test_suite: $(BUILD_DIR)/test_sorting
	@echo "📊 Running comprehensive test suite..."
	./$(BUILD_DIR)/test_sorting

# Performance testing
.PHONY: perf performance benchmark
perf performance benchmark: $(BUILD_DIR)/performance
	@echo "🚀 Running performance benchmarks..."
	./$(BUILD_DIR)/performance

# Quick benchmark (smaller sizes for quick feedback)
perf-quick: $(BUILD_DIR)/performance
	@echo "⚡ Running quick performance test..."
	@ARRAY_SIZES="100 500 1000" NUM_RUNS=3 ./$(BUILD_DIR)/performance 2>/dev/null | head -40

# Memory usage test (requires valgrind)
memtest: $(BUILD_DIR)/performance
	@if ! command -v valgrind &> /dev/null; then \
		echo "❌ Valgrind not installed. Install with: sudo apt install valgrind"; \
		exit 1; \
	fi
	@echo "🧠 Testing memory usage with Valgrind..."
	valgrind --leak-check=summary --show-leak-kinds=all ./$(BUILD_DIR)/performance 2>&1 | tail -30

# Run tests for sorting algorithms only
test_sorting: $(BUILD_DIR)/test_bubble_sort $(BUILD_DIR)/test_insertion_sort $(BUILD_DIR)/test_selection_sort $(BUILD_DIR)/test_merge_sort
	@echo "📈 Running all sorting algorithm tests..."
	@for test in $^; do \
		echo "\n--- Testing $$(basename $$test | sed 's/test_//') ---"; \
		$$test; \
	done

# Build examples
EXAMPLE_SRCS = $(wildcard examples/*.c)
EXAMPLE_BINS = $(patsubst examples/%.c,$(BUILD_DIR)/example_%,$(EXAMPLE_SRCS))

$(BUILD_DIR)/example_%: examples/%.c $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

example_%: $(BUILD_DIR)/example_%
	@echo "▶️  Running example: $*"
	./$<

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Help command
help:
	@echo "📚 Available targets:"
	@echo ""
	@echo "🏗️  Building:"
	@echo "  make all                  - Build everything (tests, examples, performance)"
	@echo "  make clean                - Remove all build artifacts"
	@echo ""
	@echo "🧪 Testing:"
	@echo "  make test_all             - Run all individual algorithm tests"
	@echo "  make test_suite           - Run comprehensive test suite"
	@echo "  make test_sorting         - Run all sorting algorithm tests"
	@echo "  make test_<algorithm>     - Run specific algorithm test (e.g., test_bubble_sort)"
	@echo ""
	@echo "🚀 Performance:"
	@echo "  make perf / performance   - Run comprehensive performance benchmarks"
	@echo "  make perf-quick           - Run quick performance test"
	@echo "  make memtest              - Test memory usage with Valgrind"
	@echo ""
	@echo "▶️  Examples:"
	@echo "  make example_<name>       - Build and run example (e.g., example_insertion_sort_demo)"
	@echo ""
	@echo "📊 Info:"
	@echo "  make help                 - Show this help message"

# Default target - build everything
all: $(BUILD_DIR) $(ALL_TESTS) $(INDIVIDUAL_TEST_BINS) $(EXAMPLE_BINS)
	@echo ""
	@echo "✅ Project built successfully!"
	@echo ""
	@echo "📋 Available commands:"
	@echo "   make test_all            # Run all correctness tests"
	@echo "   make perf                # Run performance benchmarks"
	@echo "   make example_<name>      # Run examples"
	@echo ""

# Create necessary directories if they don't exist
setup_dirs:
	mkdir -p $(TEST_UTILS_DIR)
	mkdir -p $(INCLUDE_TEST_UTILS_DIR)
	mkdir -p $(BUILD_DIR)/test_utils
