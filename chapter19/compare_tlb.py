import csv
import statistics
from collections import defaultdict

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt


def load_results(filename):
    data = defaultdict(list)

    with open(filename, newline="") as f:
        reader = csv.DictReader(f)
        for row in reader:
            pages = int(row["pages"])
            latency = float(row["ns_per_access"])
            data[pages].append(latency)

    pages = sorted(data)
    means = [statistics.mean(data[p]) for p in pages]
    stds = [statistics.stdev(data[p]) for p in pages]

    return pages, means, stds


vm_pages, vm_means, vm_stds = load_results(
    "outputs/tlb_vm.csv"
)

mac_pages, mac_means, mac_stds = load_results(
    "outputs/tlb_mac.csv"
)

plt.figure(figsize=(11, 7))

plt.errorbar(
    vm_pages,
    vm_means,
    yerr=vm_stds,
    marker="o",
    capsize=3,
    label="Ubuntu VM (4 KB/page, CPU 0 pinned)"
)

plt.errorbar(
    mac_pages,
    mac_means,
    yerr=mac_stds,
    marker="s",
    capsize=3,
    label="Mac (16 KB/page, no strict CPU pinning)"
)

plt.xscale("log", base=2)
plt.xlabel("Number of Pages")
plt.ylabel("Average Time per Access (ns)")
plt.title("TLB Performance Comparison: Ubuntu VM vs. Mac")
plt.xticks(vm_pages, [str(p) for p in vm_pages])
plt.grid(True, alpha=0.3)
plt.legend()
plt.tight_layout()

plt.savefig("outputs/tlb_comparison.png", dpi=200)

print("=== Comparison of Average Access Times ===")
print(f"{'Pages':>6} {'Ubuntu VM (ns)':>16} {'Mac (ns)':>12}")

for p, vm, mac in zip(vm_pages, vm_means, mac_means):
    print(f"{p:>6} {vm:>16.4f} {mac:>12.4f}")

print()
print("Saved graph: outputs/tlb_comparison.png")
