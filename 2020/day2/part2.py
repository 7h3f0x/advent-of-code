#!/usr/bin/env python3
import sys

def check_rule(line: str):
    rule, inp = line.split(': ')
    cnts, char = rule.split(" ")
    idx1, idx2 = map(int, cnts.split("-"))
    if inp[idx1 - 1] == char and inp[idx2 - 1] != char:
        return True
    elif inp[idx1 - 1] != char and inp[idx2 - 1] == char:
        return True
    else:
        return False

def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)
    with open(sys.argv[1], 'r') as f:
        input = f.read().splitlines()

    correct_cnt = 0
    for line in input:
        if check_rule(line):
            correct_cnt += 1
    print(correct_cnt)

if __name__ == "__main__":
    main()

"""
for sample: 1
for input: 284
"""
