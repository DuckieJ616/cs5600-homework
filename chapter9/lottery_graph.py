import subprocess
import re
import matplotlib.pyplot as plt

# Different job lengths to test
lengths = [10, 20, 50, 100, 200, 500, 1000]

# Use multiple random seeds and average the results
seeds = range(1, 21)

average_unfairness = []

for length in lengths:
    unfairness_values = []

    for seed in seeds:
        command = [
            "python3",
            "lottery.py",
            "-l",
            f"{length}:100,{length}:100",
            "-s",
            str(seed),
            "-c"
        ]

        output = subprocess.check_output(command, text=True)

        # Extract completion times
        times = [
            int(x)
            for x in re.findall(r"DONE at time (\d+)", output)
        ]

        first_completion = min(times)
        second_completion = max(times)

        # Unfairness metric
        unfairness = first_completion / second_completion
        unfairness_values.append(unfairness)

    average = sum(unfairness_values) / len(unfairness_values)
    average_unfairness.append(average)

    print(
        f"Length {length}: "
        f"Average unfairness = {average:.3f}"
    )

# Generate graph
plt.plot(lengths, average_unfairness, marker="o")

plt.xlabel("Job Length")
plt.ylabel("Average Unfairness")
plt.title("Lottery Scheduling: Unfairness vs. Job Length")
plt.ylim(0, 1.05)
plt.grid(True)

plt.savefig("lottery_unfairness.png", dpi=200, bbox_inches="tight")

print("Graph saved as lottery_unfairness.png")
