#!/usr/bin/env python3
import sys

def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)
    with open(sys.argv[1], 'r') as f:
        input = f.read().splitlines()

    input = [int(val) for val in input]
    # this is O(n), as checking existence of element in set is O(1)
    s = set(input)
    for val in s:
        if (2020 - val) in s:
            print(val * (2020 - val))
            break
    """
    # O(nlogn) due to the sorting
    input.sort()
    ptr1 = 0
    ptr2 = len(input) - 1
    while ptr1 <= ptr2:
        v = input[ptr1] + input[ptr2]
        if v > 2020:
            ptr2 -= 1
        elif v < 2020:
            ptr1 += 1
        else:
            print(input[ptr1] * input[ptr2])
            break
    """


if __name__ == "__main__":
    main()

"""
for sample: 514579
for input: 41979
"""
