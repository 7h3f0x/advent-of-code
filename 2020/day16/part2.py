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


def check_ticket(rules: dict, ticket: list) -> bool:
    _rules = []
    for rule in rules.values():
        _rules += rule

    for val in ticket:
        if not any(rule[0] <= val <= rule[1] for rule in _rules):
            return False
    return True


def possible_sequence(seq_opts: list) -> list:

    ret = [[]]
    for opts in seq_opts:
        tmp = []
        for item in opts:
            for v in ret:
                if item not in v:
                    tmp.append(v + [item])
        ret = tmp

    return ret


def get_mapping(rules: dict, other_tickets: list) -> dict:
    valid = [set(rules.keys()) for _ in other_tickets[0]]

    for ticket in other_tickets:
        if check_ticket(rules, ticket):
            # print(ticket)
            for idx, _rules in enumerate(valid):
                remove = set()
                for rule in _rules:
                    tmp = rules[rule]
                    if not any(_rule[0] <= ticket[idx] <= _rule[1] for _rule in tmp):
                        remove.add(rule)
                _rules.difference_update(remove)

    # print(valid)

    # works in any case
    # return possible_sequence(valid)

    # works in this case
    matched = dict()
    for idx, _rules in sorted(enumerate(valid), key=lambda x:len(x[1])):
        __rules = [_rule for _rule in _rules if _rule not in matched]
        assert len(__rules) == 1
        matched[__rules[0]] = idx

    return matched




def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)

    rules, my_ticket, other_tickets = parse_input(sys.argv[1])

    mapping = get_mapping(rules, other_tickets + [my_ticket])
    print(mapping)
    ans = 1
    for rule, idx in mapping.items():
        if rule.startswith("departure"):
            ans *= my_ticket[idx]

    print(ans)


if __name__ == "__main__":
    main()

"""
for sample: 71
for input: 23954
"""
