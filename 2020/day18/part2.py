#!/usr/bin/env python3
import sys
import re


OPERATORS = [
    "+",
    "*",
    '(',
    ')'
]


def parse_input(fname: str) -> list:
    with open(sys.argv[1], 'r') as f:
        return [re.findall(r"\d+|\+|\*|\(|\)", line) for line in f.read().splitlines()]


def solve(equation: list) -> int:
    operator_stack = []
    operand_stack = []

    for token in equation:
        # print(operator_stack, operand_stack)
        if token in ['+', OPERATORS[-2]]:
            operator_stack.append(token)
        elif token == '*':
            while operator_stack and operator_stack[-1] == '+':
                op = operator_stack.pop()
                arg1 = operand_stack.pop()
                arg2 = operand_stack.pop()
                res = arg1 + arg2
                operand_stack.append(res)
            operator_stack.append('*')
        elif token == OPERATORS[-1]:
            while operator_stack and operator_stack[-1] != OPERATORS[-2]:
                op = operator_stack.pop()
                arg1 = operand_stack.pop()
                arg2 = operand_stack.pop()
                if op == '+':
                    res = arg1 + arg2
                else:
                    res = arg1 * arg2
                operand_stack.append(res)
            operator_stack.pop()
        else:
                operand_stack.append(int(token))

    while operator_stack:
        op = operator_stack.pop()
        if op not in OPERATORS[:2]:
            continue
        arg1 = operand_stack.pop()
        arg2 = operand_stack.pop()
        if op == '+':
            res = arg1 + arg2
        else:
            res = arg1 * arg2
        operand_stack.append(res)

    # print(operator_stack, operand_stack)
    assert len(operator_stack) == 0
    assert len(operand_stack) == 1

    return operand_stack.pop()


def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)

    equations = parse_input(sys.argv[1])
    # print(equations)

    ans = 0
    for equation in equations[:]:
        a = solve(equation)
        # print(a)
        ans += a
        # break

    print(ans)



if __name__ == "__main__":
    main()

"""
for sample: 231, 51, 46, 1445, 669060, 23340 => 694173
for input: 43423343619505
"""
