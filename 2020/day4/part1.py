#!/usr/bin/env python3
import sys

def check_valid(passport: str) -> bool:
    passport = passport.split()
    fields = set(val.split(':')[0] for val in passport)
    if len(fields) == 8:
        return True
    elif len(fields) == 7 and "cid" not in fields:
        return True
    else:
        return False


def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)
    with open(sys.argv[1], 'r') as f:
        input = f.read().split("\n\n")

    correct_cnt = 0
    for passport in input:
        if check_valid(passport):
            correct_cnt += 1
    print(correct_cnt)

if __name__ == "__main__":
    main()

"""
for sample: 2
for input: 247
"""
