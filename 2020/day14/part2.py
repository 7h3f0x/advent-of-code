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
                instructions.append((INS_MASK, line[1]))
            else:
                res = int(line[1])
                idx = int(re.findall(r"mem\[(\d+)\]", line[0])[0])
                instructions.append((INS_MEM, (idx, res)))

    return instructions


def get_permutations(num: int, indices: list) -> list:
    res = [num]
    for idx in indices:
        tmp = []
        for n in res:
            t1 = n | (1 << idx)
            t2 = n & ~(1 << idx)
            tmp.append(t1)
            tmp.append(t2)
        res = tmp

    return res


def apply_mask(addr: int, mask: str) -> list:
    tmp = int(mask.replace('X', '0'), 2)
    addr |= tmp
    indices = [idx for idx, val in enumerate(mask[::-1]) if val == 'X']
    return get_permutations(addr, indices)


def run_instructions(instructions: str) -> dict:
    memory = dict()
    mask = "0"*36
    for ins_type, operand in instructions:
        if ins_type == INS_MASK:
            mask = operand
        else:
            # print(operand, mask)
            for addr in apply_mask(operand[0], mask):
                # print(addr)
                memory[addr] = operand[1]

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
for sample2: 208
for input: 4254673508445 
"""
