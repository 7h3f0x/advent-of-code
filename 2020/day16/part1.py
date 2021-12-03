#!/usr/bin/env python3
import sys


def parse_input(fname: str) -> tuple:
    rules = dict()
    with open(sys.argv[1], 'r') as f:
        lines = f.read().splitlines()
        g = iter(lines)

        line = next(g)
        while line:
            l = line.split(": ")
            rules[l[0]] = [[int(val) for val in r.split('-')] for r in l[1].split(" or ")]
            line = next(g)

        next(g)
        line = next(g)
        my_ticket = [int(val) for val in line.split(",")]

        next(g)
        next(g)
        other_tickets = []
        for line in g:
            other_tickets.append([int(val) for val in line.split(",")])

    return rules, my_ticket, other_tickets


def check_ticket(rules: dict, ticket: list) -> int:
    ans = 0
    _rules = []
    for rule in rules.values():
        _rules += rule

    for val in ticket:
        if not any(rule[0] <= val <= rule[1] for rule in _rules):
            ans += val
    return ans


def get_scanning_error_rate(rules: dict, other_tickets: list) -> int:
    ans = 0
    for ticket in other_tickets:
        ans += check_ticket(rules, ticket)

    return ans


def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)

    rules, _, other_tickets = parse_input(sys.argv[1])

    ans = get_scanning_error_rate(rules, other_tickets)
    print(ans)


if __name__ == "__main__":
    main()

"""
for sample: 71
for input: 23954
"""
