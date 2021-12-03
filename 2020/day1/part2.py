#!/usr/bin/env python3
import sys

def two_sum(input, sum, ptr1, ptr2):
    while ptr1 <= ptr2:
        v = input[ptr1] + input[ptr2]
        if v > sum:
            ptr2 -= 1
        elif v < sum:
            ptr1 += 1
        else:
            return ptr1, ptr2
    return None

def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)
    with open(sys.argv[1], 'r') as f:
        input = f.read().splitlines()

    input = [int(val) for val in input]
    input.sort()

    ptr1 = 0
    ptr3 = len(input) - 1

    ptr2 = ptr1 + 1
    while ptr1 < len(input):
        v = two_sum(input, 2020 - input[ptr1], ptr2, ptr3)
        if v is None:
            ptr1 += 1
            ptr2 += 1
            continue
        p1 , p2 = v
        print(input[ptr1] * input[p1] * input[p2])
        break


if __name__ == "__main__":
    main()

"""
for sample: 241861950
for input: 193416912
"""
