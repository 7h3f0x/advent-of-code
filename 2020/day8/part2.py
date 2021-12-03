#!/usr/bin/env python3
import sys


def run_instructions(instructions: list) -> tuple:
    """
    returns status, `accumulator` value
    status = 2, if access way out of bounds
    status = 1, if infinite loop occured
    status = 0, if program tries to execute after last instruction
    """

    num_instructions = len(instructions)
    idx = 0
    accumulator = 0
    is_executed = [0 for _ in instructions]

    while True:
        if idx == num_instructions:
            break
        elif idx > num_instructions:
            return 2, accumulator
        elif is_executed[idx] == 0:
            is_executed[idx] = 1
        else:
            return 1, accumulator

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

    return 0, accumulator


def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)
    with open(sys.argv[1], 'r') as f:
        instructions = f.read().splitlines()

    instructions = [instruction.split(" ") for instruction in instructions]
    instructions = [(op, int(arg)) for op, arg in instructions]

    switch = {
        "nop": "jmp",
        "jmp": "nop"
    }


    for idx, (op, arg) in enumerate(instructions):
        if op == "acc":
            continue
        elif op in ["nop", "jmp"]:
            instructions[idx] = (switch[op], arg)
            status, accumulator = run_instructions(instructions)
            if status == 0:
                print(accumulator)
                break
            else:
                instructions[idx] = (op, arg)
        else:
            raise Exception("Unknown instruction `{}` at index `{}`".format(op, idx))


if __name__ == "__main__":
    main()

"""
for sample: 8
for input: 1125
"""

