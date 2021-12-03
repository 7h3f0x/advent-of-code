#!/usr/bin/env python3
import sys

decode = {
    "B": 1,
    "F": 0,
    "R": 1,
    "L": 0
}


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

    passes = set(get_val(line) for line in input)
    for i in range(1, 2**(7+3) - 1):
        if i not in passes and (i-1) in passes and (i+1) in passes:
            print(i)

if __name__ == "__main__":
    main()

"""
for input: 649
"""
