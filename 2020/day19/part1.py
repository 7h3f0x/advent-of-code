#!/usr/bin/env python3
import sys
import re

class Checker:
    def _concat_rule(self, rule):
        return ''.join(list(map(lambda x: f"({self._get_rule(int(x))})", rule)))

    def _get_rule(self, idx) -> str:
        rule = self.rules[idx]
        if type(rule[0]) == str:
            if len(rule) == 1:
                ch = rule[0].replace('"', '')
                if ch == 'a' or ch == 'b':
                    return ch
                else:
                    return self._get_rule(int(ch))
            return self._concat_rule(rule)
        elif type(rule[0]) == list:
            return '|'.join(list(map(lambda x: f"({self._concat_rule(x)})", rule)))
        else:
            pass

    def __init__(self, rules):
        self.rules = rules
        self.regex = re.compile(self._get_rule(0))
        # print(self._get_rule(0))

    def check(self, message: str) -> bool:
        if self.regex.fullmatch(message):
            return True
        return False


def parse_input(fname: str) -> tuple:
    active_states = set()
    with open(fname, 'r') as f:
        rules_str, messages_str = f.read().split("\n\n")
    rules = {}
    SEPARATOR = ": "
    for rule_str in rules_str.splitlines():
        idx, rule = rule_str.split(SEPARATOR)
        idx = int(idx)
        rule = rule.split(' | ')
        if len(rule) == 1:
            rules[idx] = rule[0].split(' ')
        else:
            rules[idx] = list(map(lambda x: x.split(' '), rule))

    messages = messages_str.splitlines()
    return rules, messages


def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)

    rules, messages = parse_input(sys.argv[1])
    # print(rules)
    checker = Checker(rules)
    result = sum(1 for message in messages if checker.check(message))
    print(result)



if __name__ == "__main__":
    main()

"""
for sample: 2
for input: 104
"""

