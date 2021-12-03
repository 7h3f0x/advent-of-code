#!/usr/bin/env python3
import sys


def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)
    with open(sys.argv[1], 'r') as f:
        input = f.read().splitlines()

    trees = 0
    x = 0
    pattern_len = len(input[0])
    for row in input:
        if row[x] == '#':
            trees += 1
        x = (x + 3) % pattern_len
    print(trees)

if __name__ == "__main__":
    main()

"""
for sample: 7
for input: 214
"""
