#!/usr/bin/env python3
import sys


def get_trees(right: int, down: int, input: list) -> int:
    trees = 0
    x = 0
    pattern_len = len(input[0])
    bottom = len(input)
    y = 0
    while y < bottom:
        if input[y][x] == '#':
            trees += 1
        x = (x + right) % pattern_len
        y += down
    return trees

def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)
    with open(sys.argv[1], 'r') as f:
        input = f.read().splitlines()

    t1 = get_trees(1, 1, input)
    t2 = get_trees(3, 1, input)
    t3 = get_trees(5, 1, input)
    t4 = get_trees(7, 1, input)
    t5 = get_trees(1, 2, input)
    print(t1 * t2 * t3 * t4 * t5)

if __name__ == "__main__":
    main()

"""
for sample: 336
for input: 8336352024
"""
