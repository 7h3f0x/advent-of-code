#!/usr/bin/env python3
import sys
import re

class Checker:
    def _concat_rule(self, rule: list, depth: int) -> str:
        return ''.join(list(map(lambda x: f"({self._get_rule(int(x), depth)})", rule)))

    # https://0xdf.gitlab.io/adventofcode2020/19
    # dont know why `+` in re library wasn't working
    def _get_rule(self, idx: int, depth=15) -> str:
        if depth == 0:
            return ''
        rule = self.rules[idx]
        if type(rule[0]) == str:
            if len(rule) == 1:
                ch = rule[0].replace('"', '')
                if ch == 'a' or ch == 'b':
                    return f"{ch}"
                else:
                    return self._get_rule(int(ch), depth-1)
            return self._concat_rule(rule, depth-1)
        elif type(rule[0]) == list:
            return '|'.join(list(map(lambda x: f"({self._concat_rule(x, depth-1)})", rule)))
        else:
            pass

    def __init__(self, rules: dict):
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
    """
    patched rules:
    8 : 42 | 42 8
    11: 42 31 | 42 11 31
    """
    rules[8] = [['42'], ['42', '8']]
    rules[11] = [['42', '31'], ['42', '11', '31']]
    # print(rules)
    checker = Checker(rules)
    # for message in messages:
    #     if checker.check(message):
    #         print(message)
    result = sum(1 for message in messages if checker.check(message))
    print(result)



if __name__ == "__main__":
    main()

"""
for sample2: 12
for input: 104
"""

