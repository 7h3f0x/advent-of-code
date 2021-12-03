#!/usr/bin/env python3
import sys

decode = {
    "B": 1,
    "F": 0,
    "R": 1,
    "L": 0
}


def cmp(pass1: str, pass2: str) -> int:
    for c1, c2 in zip(pass1, pass2):
        if decode[c1] > decode[c2]:
            return 1
        elif decode[c1] < decode[c2]:
            return -1
        else:
            continue
    return 0


def get_val(pass_id: str) -> int:
    num = 0
    for char in pass_id:
        num = num << 1
        num += decode[char]
    return num

def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)
    with open(sys.argv[1], 'r') as f:
        input = f.read().splitlines()

    val_max = "F" * 7 + "L" * 3
    for line in input:
        # print(get_val(line))
        if cmp(line, val_max) == 1:
            val_max = line

    print(get_val(val_max))


if __name__ == "__main__":
    main()

"""
for sample: 820
for input: 835
"""
