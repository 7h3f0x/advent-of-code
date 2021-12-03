#!/usr/bin/env python3
import sys
from pprint import pprint


movements = [
    (0, 1),
    (1, 0),
    (0, -1),
    (-1, 0),
    (1, 1),
    (1, -1),
    (-1, 1),
    (-1, -1)
]


def get_adjacent_seats(seats: list, row_idx: int, col_idx: int) -> int:
    cnt = 0
    l1 = len(seats)
    l2 = len(seats[0])

    for x, y in movements:
        row = row_idx + x
        col = col_idx + y
        if 0 <= row < l1 and 0 <= col < l2:
            if seats[row][col] == '#':
                cnt += 1

    return cnt



def occupy_seats(seats: list) -> bool:
    # pprint(seats)
    ret_val = False
    orig_seats = [line[::] for line in seats]

    for row_idx in range(len(seats)):
        for col_idx in range(len(seats[row_idx])):
            if orig_seats[row_idx][col_idx] == ".":
                continue
            elif orig_seats[row_idx][col_idx] == "#":
                tmp = get_adjacent_seats(orig_seats, row_idx, col_idx)
                if tmp >= 4:
                    # print(tmp)
                    seats[row_idx][col_idx] = "L"
                    ret_val = True
            else:
                if get_adjacent_seats(orig_seats, row_idx, col_idx) == 0:
                    seats[row_idx][col_idx] = "#"
                    ret_val = True

    return ret_val

def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)
    with open(sys.argv[1], 'r') as f:
        input = [list(line) for line in f.read().splitlines()]

    while True:
        if not occupy_seats(input):
            break


    res = 0
    for line in input:
        res += sum(char == "#" for char in line)
    print(res)


if __name__ == "__main__":
    main()

"""
for sample: 37
for input: 2406
"""
