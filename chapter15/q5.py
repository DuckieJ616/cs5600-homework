import subprocess
import re
import matplotlib.pyplot as plt

limits = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
seeds = [1, 2, 3]
rates = []

for limit in limits:
    seed_rates = []

    for seed in seeds:
        result = subprocess.run(
            [
                "python3",
                "relocation.py",
                "-s", str(seed),
                "-a", "1024",
                "-p", "16384",
                "-n", "1000",
                "-l", str(limit),
                "-c"
            ],
            capture_output=True,
            text=True,
            check=True
        )

        valid = len(re.findall(r"-->\s+VALID:", result.stdout))
        seed_rates.append(valid / 1000 * 100)

    avg_rate = sum(seed_rates) / len(seed_rates)
    rates.append(avg_rate)
    print(f"Limit={limit}, Valid Rate={avg_rate:.2f}%")

plt.plot(limits, rates, marker="o")
plt.xlabel("Limit Register (bytes)")
plt.ylabel("Valid Address Rate (%)")
plt.title("Chapter 15 Q5: Limit vs Valid Address Rate")
plt.grid(True)
plt.savefig("/home/xinyi-jiang/hw5/chapter15/q5_graph.png")
print("Graph saved successfully.")
