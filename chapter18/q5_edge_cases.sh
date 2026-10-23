#!/bin/bash

mkdir -p outputs

run_test() {
    name="$1"
    shift

    echo "Running $name"

    python3 paging-linear-translate.py "$@" \
        > "outputs/${name}.txt" 2>&1

    echo "Exit code: $?" >> "outputs/${name}.txt"
}

# 1. Virtual memory larger than physical memory
run_test q5_virtual_gt_physical \
    -a 64k -p 16k -P 4k -c

# 2. Page size larger than virtual address space
run_test q5_page_gt_address \
    -a 4k -p 64k -P 8k -c

# 3. Page size larger than physical memory
run_test q5_page_gt_physical \
    -a 64k -p 4k -P 8k -c

# 4. Non-power-of-two virtual address space
run_test q5_non_power_two \
    -a 24k -p 96k -P 3k -c

# 5. Physical memory smaller than virtual memory
run_test q5_minimal_physical \
    -a 16k -p 4k -P 4k -c

# 6. Zero valid pages
run_test q5_zero_used \
    -a 16k -p 64k -P 4k -u 0 -c

# 7. All pages valid
run_test q5_full_used \
    -a 16k -p 64k -P 4k -u 100 -c

# 8. Equal virtual and physical memory
run_test q5_equal_memory \
    -a 16k -p 16k -P 4k -c

# 9. Physical memory larger than virtual memory
run_test q5_physical_larger \
    -a 16k -p 32k -P 4k -c

# 10. Non-power-of-two page size
run_test q5_non_power_page \
    -a 16k -p 64k -P 3k -c

echo "All 10 edge-case tests completed."
