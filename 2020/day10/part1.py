#!/usr/bin/env python3
import sys


def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)
    with open(sys.argv[1], 'r') as f:
        input = [int(val) for val in f.read().splitlines()]

    input.append(0)
    input.sort()

    one_diff = 0
    three_diff = 1 # since at the end, diff would be 3 jolts from highest adapter to device
    for idx in range(1, len(input)):
        if input[idx] - input[idx - 1] == 1:
            one_diff += 1
        elif input[idx] - input[idx - 1] == 3:
            three_diff += 1
        else:
            print(f"Found diff of {input[idx] - input[idx - 1]} for values {input[idx]}, {input[idx - 1]}")

    print(one_diff, three_diff, one_diff * three_diff)


if __name__ == "__main__":
    main()

"""
for sample1: 7 5 35
for sample2: 22 10 220
for input: 69 40 2760
"""
