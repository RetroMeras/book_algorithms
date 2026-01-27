CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -Iinclude/test_utils
BUILD_DIR = build
TEST_DIR = tests
TEST_UTILS_DIR = $(TEST_DIR)/test_utils

# Source files
SRCS = $(shell find src -name '*.c')
OBJS = $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Test utility files
TEST_UTILS_SRCS = $(filter-out $(TEST_UTILS_DIR)/performance.c, $(wildcard $(TEST_UTILS_DIR)/*.c))
TEST_UTILS_OBJS = $(patsubst $(TEST_UTILS_DIR)/%.c,$(BUILD_DIR)/test_utils/%.o,$(TEST_UTILS_SRCS))

# Individual test files
INDIVIDUAL_TEST_SRCS = $(filter-out $(TEST_UTILS_DIR)/%, $(wildcard $(TEST_DIR)/*.c))
INDIVIDUAL_TEST_BINS = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/test_%,$(INDIVIDUAL_TEST_SRCS))

# Main test programs
ALL_TESTS = $(BUILD_DIR)/test_sorting $(BUILD_DIR)/performance

.PHONY: all clean help test test_all test_% perf performance memtest \
        gdb gdb_% lldb lldb_% valgrind valgrind_% debug

# ========== BUILD RULES ==========

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

# Compile test utility files
$(BUILD_DIR)/test_utils/%.o: $(TEST_UTILS_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build individual test executables
$(BUILD_DIR)/test_%: $(TEST_DIR)/%.c $(TEST_UTILS_OBJS) $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Build comprehensive test suite
$(BUILD_DIR)/test_sorting: tests/test_sorting.c $(TEST_UTILS_OBJS) $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Build performance test executable
$(BUILD_DIR)/performance: tests/test_utils/performance.c $(TEST_UTILS_OBJS) $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< $(TEST_UTILS_OBJS) $(OBJS) -o $@ -lm

# ========== DEBUGGING TARGETS ==========

# Run test with GDB (auto-break at main)
gdb_%: $(BUILD_DIR)/test_%
	@echo "🔍 Starting GDB for $* (break at main)..."
	gdb -ex "break main" -ex "run" --args $<

# Run comprehensive test suite with GDB
gdb: $(BUILD_DIR)/test_sorting
	@echo "🔍 Starting GDB for comprehensive test suite..."
	gdb -ex "break main" -ex "run" --args $<

# Run performance test with GDB
gdb_perf: $(BUILD_DIR)/performance
	@echo "🔍 Starting GDB for performance tests..."
	gdb -ex "break main" -ex "run" --args $<

# Run test with LLDB (auto-break at main)
lldb_%: $(BUILD_DIR)/test_%
	@echo "🔍 Starting LLDB for $* (break at main)..."
	lldb -o "breakpoint set --name main" -o "run" $<

# Run comprehensive test suite with LLDB
lldb: $(BUILD_DIR)/test_sorting
	@echo "🔍 Starting LLDB for comprehensive test suite..."
	lldb -o "breakpoint set --name main" -o "run" $<

# Run performance test with LLDB
lldb_perf: $(BUILD_DIR)/performance
	@echo "🔍 Starting LLDB for performance tests..."
	lldb -o "breakpoint set --name main" -o "run" $<

# Run test with Valgrind (memory checking)
valgrind_%: $(BUILD_DIR)/test_%
	@echo "🧠 Running Valgrind memory check for $*..."
	@if ! command -v valgrind &> /dev/null; then \
		echo "❌ Valgrind not installed. Install with: sudo apt install valgrind"; \
		exit 1; \
	fi
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $<

# Run comprehensive test suite with Valgrind
valgrind: $(BUILD_DIR)/test_sorting
	@echo "🧠 Running Valgrind memory check for comprehensive test suite..."
	@if ! command -v valgrind &> /dev/null; then \
		echo "❌ Valgrind not installed. Install with: sudo apt install valgrind"; \
		exit 1; \
	fi
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $<

# Run performance test with Valgrind
valgrind_perf: $(BUILD_DIR)/performance
	@echo "🧠 Running Valgrind memory check for performance tests..."
	@if ! command -v valgrind &> /dev/null; then \
		echo "❌ Valgrind not installed. Install with: sudo apt install valgrind"; \
		exit 1; \
	fi
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $<

# ========== REGULAR TESTING TARGETS ==========

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
perf performance: $(BUILD_DIR)/performance
	@echo "🚀 Running performance benchmarks..."
	./$(BUILD_DIR)/performance

# Quick benchmark
perf-quick: $(BUILD_DIR)/performance
	@echo "⚡ Running quick performance test..."
	@ARRAY_SIZES="100 500 1000" NUM_RUNS=3 ./$(BUILD_DIR)/performance 2>/dev/null | head -40

# Memory usage test
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

# Help command with debug info
help:
	@echo "📚 Available targets:"
	@echo ""
	@echo "🏗️  Building:"
	@echo "  make all                  - Build everything"
	@echo "  make clean                - Remove build artifacts"
	@echo ""
	@echo "🧪 Testing:"
	@echo "  make test_all             - Run all individual tests"
	@echo "  make test_suite           - Run comprehensive test suite"
	@echo "  make test_<algorithm>     - Run specific test (e.g., test_bubble_sort)"
	@echo ""
	@echo "🐛 Debugging:"
	@echo "  make gdb_<algorithm>      - Debug test with GDB"
	@echo "  make gdb                  - Debug comprehensive test suite with GDB"
	@echo "  make gdb_perf             - Debug performance tests with GDB"
	@echo "  make lldb_<algorithm>     - Debug test with LLDB"
	@echo "  make lldb                 - Debug comprehensive test suite with LLDB"
	@echo "  make lldb_perf            - Debug performance tests with LLDB"
	@echo "  make valgrind_<algorithm> - Run memory check with Valgrind"
	@echo "  make valgrind             - Run memory check on comprehensive suite"
	@echo "  make valgrind_perf        - Run memory check on performance tests"
	@echo ""
	@echo "🚀 Performance:"
	@echo "  make perf                 - Run performance benchmarks"
	@echo "  make perf-quick           - Run quick performance test"
	@echo "  make memtest              - Test memory usage"
	@echo ""
	@echo "▶️  Examples:"
	@echo "  make example_<name>       - Build and run example"
	@echo ""
	@echo "📊 Info:"
	@echo "  make help                 - Show this help"

# Default target
all: $(BUILD_DIR) $(ALL_TESTS) $(INDIVIDUAL_TEST_BINS) $(EXAMPLE_BINS)
	@echo ""
	@echo "✅ Project built successfully!"
	@echo ""
	@echo "📋 Available debug commands:"
	@echo "   make gdb_bubble_sort     # Debug bubble sort test"
	@echo "   make lldb_insertion_sort # Debug insertion sort test with LLDB"
	@echo "   make valgrind_merge_sort # Check memory leaks in merge sort test"
	@echo "   make gdb                 # Debug comprehensive test suite"
	@echo ""
