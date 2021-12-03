#!/usr/bin/env python3
import sys


directions_move_90 = {
    'R': lambda x, y : [-y, x],
    'L': lambda x, y : [y, -x]
}


def result_coordinates(movements: list) -> tuple:
    x = y = 0

    waypoint = [1, 10]
    for action, val in movements:
        if action == 'E':
            waypoint[1] += val
        elif action == 'W':
            waypoint[1] -= val
        elif action == 'N':
            waypoint[0] += val
        elif action == 'S':
            waypoint[0] -= val
        elif action == 'F':
            x += val * waypoint[0]
            y += val * waypoint[1]
        else:
            v = val // 90
            for _ in range(v):
                waypoint = directions_move_90[action](*waypoint)

    return x, y



def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)
    with open(sys.argv[1], 'r') as f:
        input = [(line[0], int(line[1:])) for line in f.read().splitlines()]

    x, y = result_coordinates(input)
    print(f"{x} , {y} => {abs(x) + abs(y)}")


if __name__ == "__main__":
    main()

"""
for sample: -72 214 286
for input: -16645 -11946 28591
"""
