#!/usr/bin/env python3
import sys
import re

ecl_valid_list = "amb blu brn gry grn hzl oth".split()


def check_height(height: str) -> bool:
    if height[-2:] == "cm":
        return 150 <= int(height[:-2]) <= 193
    elif height[-2:] == "in":
        return 59 <= int(height[:-2]) <= 76
    else:
        return False

def check_valid(passport: str) -> bool:
    passport = passport.split()
    fields = dict(val.split(':') for val in passport)
    if len(fields) == 8 or (len(fields) == 7 and "cid" not in fields):
        if not 1920 <= int(fields['byr']) <= 2020:
            return False
        if not 2010 <= int(fields['iyr']) <= 2020: 
            return False
        if not 2020 <= int(fields['eyr']) <= 2030:
            return False
        if not check_height(fields['hgt']):
            return False
        # ^, $ -> for getting exact match
        # as ^ is start of text, $ is end of text
        if not re.match(r"^#[0-9a-f]{6}$", fields['hcl']): 
            return False
        if fields['ecl'] not in ecl_valid_list:
            return False
        if not re.match(r"^[0-9]{9}$", fields['pid']):
            return False
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
for input: 145
"""
