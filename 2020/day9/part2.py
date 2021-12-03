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


def find_numbers_with_sum(numbers: list, target_sum: int) -> tuple:
    idx1 = 0
    idx2 = idx1 + 1
    curr_sum = numbers[idx1] + numbers[idx2]
    while True:
        if curr_sum == target_sum:
            return idx1, idx2
        elif curr_sum < target_sum:
            idx2 += 1
            curr_sum += numbers[idx2]
        else:
            curr_sum -= numbers[idx1]
            idx1 += 1


def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)
    with open(sys.argv[1], 'r') as f:
        input = [int(val) for val in f.read().splitlines()]

    # for sample
    # ans = find_first_not_following(input, 5)

    ans = find_first_not_following(input, 25)

    idx1, idx2 = find_numbers_with_sum(input, ans)

    min_num = min(input[idx1:idx2 + 1])
    max_num = max(input[idx1:idx2 + 1])
    print(min_num + max_num)


if __name__ == "__main__":
    main()

"""
for sample: 62
for input: 2986195
"""

