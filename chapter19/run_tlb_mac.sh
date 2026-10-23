#!/bin/bash
set -euo pipefail

OUTPUT="outputs/tlb_mac.csv"

echo "pages,iterations,ns_per_access,run" > "$OUTPUT"

echo "=== Mac System ==="
uname -m
getconf PAGESIZE

for pages in 1 2 4 8 16 32 64 128 256 512 1024 2048 4096; do
    iterations=$((10000000 / pages))

    for run in 1 2 3 4 5; do
        result=$(./tlb_mac "$pages" "$iterations")
        echo "$result,$run" >> "$OUTPUT"
    done

    echo "Completed: $pages pages"
done

echo "=== Results ==="
head -10 "$OUTPUT"

echo "=== Total measurements ==="
wc -l "$OUTPUT"
