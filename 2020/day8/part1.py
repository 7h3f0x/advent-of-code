#!/usr/bin/env python3
import sys


def run_till_repeat(instructions: list) -> int:
    instructions = [instruction.split(" ") for instruction in instructions]
    instructions = [(op, int(arg)) for op, arg in instructions]

    idx = 0
    accumulator = 0
    is_executed = [0 for _ in instructions]

    while True:
        if is_executed[idx] == 0:
            is_executed[idx] = 1
        else:
            return accumulator

        op, arg = instructions[idx]
        if op == "nop":
            pass
        elif op == "acc":
            accumulator += arg
        elif op == "jmp":
            idx += arg
            continue
        else:
            raise Exception("Unknown instruction `{}` at index `{}`".format(op, idx))

        idx += 1

    return 0


def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)
    with open(sys.argv[1], 'r') as f:
        instructions = f.read().splitlines()

    ret_val = run_till_repeat(instructions)
    print(ret_val)


if __name__ == "__main__":
    main()

"""
for sample: 5
for input: 1137
"""
