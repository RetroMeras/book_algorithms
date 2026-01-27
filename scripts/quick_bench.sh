#!/bin/bash

echo "Quick Performance Benchmark"
echo "=========================="

# Build if needed
make performance 2>/dev/null

# Run with smaller sizes for quick feedback
echo "Running quick benchmark (small sizes)..."
echo ""

# Temporary config for quick test
cat > /tmp/quick_perf.c << 'EOF'
#include "perf.h"
#include <stdio.h>

int main() {
    size_t sizes[] = {100, 500, 1000};
    perf_config_t config = {
        .sizes = sizes,
        .num_sizes = 3,
        .num_runs_per_size = 3,
        .min_value = -1000,
        .max_value = 1000
    };
    
    benchmark_sorting_algorithms(&config);
    return 0;
}
EOF

gcc -Iinclude -Isrc tests/performance.c tests/test_utils.c src/sorting/*.c src/common.c -o /tmp/quick_bench -lm
/tmp/quick_bench
