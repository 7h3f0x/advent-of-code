#!/usr/bin/env python3
import sys
import re


def parse_input(fname: str) -> list:
    list_nums = []
    with open(sys.argv[1], 'r') as f:
        for line in f:
            line = line.strip()
            list_nums.append([int(val) for val in line.split(',')])

    return list_nums


def find_nth(nums: list, n: int) -> int:
    mem = {}
    curr = None
    for idx in range(n):
        prev = curr
        if idx < len(nums):
            curr = nums[idx]
        else:
            if prev in mem:
                curr = idx - mem[prev]
            else:
                curr = 0
        mem[prev] = idx
        # print(prev, idx)

    return curr

def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)

    list_nums = parse_input(sys.argv[1])
    # print(list_nums)

    for nums in list_nums:
        print(find_nth(nums, 2020))
        # break


if __name__ == "__main__":
    main()

"""
for samples: 436, 1, 10, 27, 78, 438, 1836
for input: 639
"""
