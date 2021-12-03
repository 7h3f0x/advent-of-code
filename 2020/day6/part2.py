#!/usr/bin/env python3
import sys


def get_ques_count(group: str) -> int:
    ques = dict()
    group = group.splitlines()
    for person in group:
        for char in person:
            ques[char] = ques.get(char, 0) + 1
    return sum(ques[char] == len(group) for char in ques)


def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)
    with open(sys.argv[1], 'r') as f:
        input = f.read().split("\n\n")

    tot_ques_cnt = 0
    for group in input:
        tot_ques_cnt += get_ques_count(group)

    print(tot_ques_cnt)

if __name__ == "__main__":
    main()

"""
for sample: 6
for input: 3235
"""
