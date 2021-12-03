#!/usr/bin/env python3
import sys
import re


INS_MASK = 0
INS_MEM = 1


def parse_input(fname: str) -> list:
    instructions = []
    with open(sys.argv[1], 'r') as f:
        for line in f:
            line = line.strip().split(' = ')
            if line[0] == "mask":
                res = list()
                for idx, val in enumerate(line[1][::-1]):
                    if val != 'X':
                        res.append((idx, int(val)))
                instructions.append((INS_MASK, res))
            else:
                res = int(line[1])
                idx = int(re.findall(r"mem\[(\d+)\]", line[0])[0])
                instructions.append((INS_MEM, (idx, res)))

    return instructions


def run_instructions(instructions: str) -> dict:
    memory = dict()
    zero_mask = 0xfffffffff
    one_mask = 0x000000000
    for ins_type, operand in instructions:
        if ins_type == INS_MASK:
            zero_mask = 0xfffffffff
            one_mask = 0x000000000
            for idx, val in operand:
                if val == 1:
                    one_mask |= 1 << idx
                else:
                    zero_mask &= ~(1 << idx)
        else:
            memory[operand[0]] = (operand[1] | one_mask) & zero_mask

    return memory


def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)

    instructions = parse_input(sys.argv[1])
    # print(instructions)

    memory = run_instructions(instructions)
    # print(memory)
    ans = 0
    for key in memory:
        ans += memory[key]

    print(ans)



if __name__ == "__main__":
    main()

"""
for sample: 165
for input: 18630548206046
"""
