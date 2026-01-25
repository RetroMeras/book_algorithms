# Algorithms & Data Structures Practice Project

A C-based project for studying and implementing algorithms and data structures, designed as a companion to algorithm textbooks and learning resources.

## 📁 Project Structure

```
.
├── build/              # Compiled object files and executables
├── examples/           # Example programs demonstrating algorithms
├── include/            # Header files
│   ├── common.h
│   └── sorting/        # Algorithm-specific headers
├── src/                # Source code implementations
│   ├── common.c        # Shared utilities
│   └── sorting/        # Algorithm implementations
├── tests/              # Unit tests
└── Makefile
```

## 🛠️ Build System

### Prerequisites
- GCC compiler
- Make
- (Optional) Bear for `compile_commands.json` generation

### Available Make Commands

#### Building
```bash
make all                    # Create build directories (default)
make                       # Same as 'make all'
```

#### Testing
```bash
make test_sorting          # Build and run sorting algorithm tests
```

#### Examples
```bash
make example_insertion_sort_demo  # Build and run insertion sort visualization
make example_%             # Pattern: Build and run any example (e.g., make example_bubble_sort)
```

#### Development
```bash
make clean                 # Remove all build artifacts
make compile_commands.json # Generate compilation database for tooling (requires bear)
make help                  # Display available commands
```

## 📚 Implemented Algorithms

### Sorting Algorithms
- **Insertion Sort** (`src/sorting/insertion_sort.c`)
  - Time: O(n²) worst, O(n) best case
  - Space: O(1)
  - Stable: Yes
  - Best for: Small or nearly sorted arrays

## 🧪 Testing

Run comprehensive tests to verify algorithm correctness:
```bash
make test_sorting
```

Tests cover:
- Basic sorting functionality
- Already sorted arrays
- Reverse sorted arrays
- Arrays with duplicate values
- Single-element arrays

## 📖 Learning Examples

The project includes educational examples that demonstrate algorithm behavior step-by-step:

```bash
make example_insertion_sort_demo
```

This shows:
- Step-by-step sorting process
- Current element highlighting
- Performance characteristics
- Best/worst case scenarios

## 🔧 Development Guidelines

### Adding New Algorithms

1. **Create implementation** in appropriate `src/` subdirectory:
   ```c
   // src/sorting/bubble_sort.c
   #include "sorting/sorting.h"
   
   void bubble_sort(int *arr, size_t n) {
       // Implementation
   }
   ```

2. **Add header declaration** in `include/sorting/sorting.h`:
   ```c
   // Bubble Sort
   // Time: O(n²) | Space: O(1)
   void bubble_sort(int *arr, size_t n);
   ```

3. **Create tests** in `tests/` directory
4. **Add example** in `examples/` directory (optional)

### Adding Tests

Follow the pattern in `tests/test_sorting.c`:
```c
void test_algorithm_scenario() {
    // Setup
    // Execute
    // Verify with assert()
    // Print success message
}
```

### Code Style
- Use descriptive function names and comments
- Include time/space complexity in header files
- Follow consistent error handling patterns
- Document edge cases

## 📊 Performance Characteristics

Each algorithm includes documentation of:
- Time complexity (best/average/worst case)
- Space complexity
- Stability
- Appropriate use cases
- Comparison with alternatives

## 🎯 Learning Objectives

This project is designed to help you:
- Understand algorithm design principles
- Implement algorithms from scratch
- Analyze time and space complexity
- Test algorithm correctness
- Visualize algorithm execution
- Compare algorithm performance

## 🔍 IDE Integration

For better development experience:
```bash
make compile_commands.json
```
Then configure your editor to use the generated `compile_commands.json` for:
- Code completion
- Error highlighting
- Go-to-definition
- Refactoring tools

## 📚 Resources

- "Introduction to Algorithms" by CLRS
- "Algorithm Design Manual" by Skiena
- "Grokking Algorithms" by Bhargava
- Online resources: GeeksforGeeks, LeetCode, HackerRank

---

*Happy coding and learning! Remember: Understanding beats memorization every time.* 🚀
