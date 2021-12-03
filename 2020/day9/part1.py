#!/usr/bin/env python3
import sys


def get_possibilities(numbers: list) -> list:
    res = []
    for idx1 in range(len(numbers) - 1):
        for idx2 in range(idx1, len(numbers)):
            res.append(numbers[idx1] + numbers[idx2])
    return res


def find_first_not_following(numbers: list, preamble_len: int) -> int:
    for idx in range(preamble_len, len(numbers)):
        if numbers[idx] not in get_possibilities(numbers[idx - preamble_len: idx]):
            return numbers[idx]

def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)
    with open(sys.argv[1], 'r') as f:
        input = [int(val) for val in f.read().splitlines()]

    # for sample
    # ans = find_first_not_following(input, 5)

    ans = find_first_not_following(input, 25)
    print(ans)


if __name__ == "__main__":
    main()

"""
for sample: 127
for input: 21806024
"""
