import csv
import statistics
from collections import defaultdict
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

data = defaultdict(list)

with open("outputs/tlb_vm.csv", newline="") as f:
    reader = csv.DictReader(f)
    for row in reader:
        pages = int(row["pages"])
        latency = float(row["ns_per_access"])
        data[pages].append(latency)

pages = sorted(data)
means = [statistics.mean(data[p]) for p in pages]
stds = [
    statistics.stdev(data[p]) if len(data[p]) > 1 else 0
    for p in pages
]

plt.figure(figsize=(10, 6))
plt.errorbar(
    pages,
    means,
    yerr=stds,
    marker="o",
    capsize=3
)

plt.xscale("log", base=2)
plt.xlabel("Number of Pages")
plt.ylabel("Average Time per Access (ns)")
plt.title("TLB Performance — Ubuntu VM (Single CPU)")
plt.grid(True, alpha=0.3)
plt.tight_layout()

plt.savefig("outputs/tlb_vm.png", dpi=200)

print("=== Average Results ===")
for p, mean, std in zip(pages, means, stds):
    print(f"{p:5d} pages: {mean:.4f} ns ± {std:.4f}")

print("Graph saved to outputs/tlb_vm.png")
