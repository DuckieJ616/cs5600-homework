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

# Case 1: Virtual memory larger than physical memory
run_test q4_virtual_gt_physical \
    -a 64k -p 16k -P 4k -c

# Case 2: Page size larger than address space
run_test q4_page_gt_address \
    -a 4k -p 64k -P 8k -c

# Case 3: Page size larger than physical memory
run_test q4_page_gt_physical \
    -a 64k -p 4k -P 8k -c

# Case 4: Non-power-of-two page size
run_test q4_non_power_two \
    -a 24k -p 96k -P 3k -c

# Case 5: Minimal physical memory
run_test q4_minimal_physical \
    -a 16k -p 4k -P 4k -c

# Case 6: Zero valid pages
run_test q4_zero_used \
    -a 16k -p 64k -P 4k -u 0 -c

# Case 7: All pages valid
run_test q4_full_used \
    -a 16k -p 64k -P 4k -u 100 -c

echo "All tests completed."
