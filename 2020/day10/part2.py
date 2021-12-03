#!/usr/bin/env python3
import sys


def get_possibilities_recursive(input: list, start_idx=0) -> int:
    """
    Recusive solution
    O(3 ^ |input|)
    """
    if start_idx == len(input) - 1:
        return 1

    res = 0
    for i in range(1, 4):
        try:
            if input[start_idx + i] - input[start_idx] <= 3:
                res += get_possibilities_recursive(input, start_idx + i)
            else:
                break
        except IndexError:
            break

    return res


def get_possibilities_dp(input: list) -> int:
    """
    Dynamic Programming based solution
    O(|input|)
    """
    # possibilities from some idx onwards
    possibilities = [ 0 for _ in range(len(input)) ]
    possibilities[-1] = 1
    for idx in range(len(input) - 2, -1, -1):
        for i in range(1, 4):
            try:
                if input[idx + i] - input[idx] <= 3:
                    possibilities[idx] += possibilities[idx + i]
                else:
                    break
            except IndexError:
                break

    return possibilities[0]


def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)
    with open(sys.argv[1], 'r') as f:
        input = [int(val) for val in f.read().splitlines()]

    input.append(0)
    input.sort()

    # recusive solution is too time consuming for `input`
    # possibilities = get_possibilities_recursive(input)

    possibilities = get_possibilities_dp(input)
    print(possibilities)


if __name__ == "__main__":
    main()

"""
for sample1: 8
for sample2: 19208
for input: 13816758796288
"""
