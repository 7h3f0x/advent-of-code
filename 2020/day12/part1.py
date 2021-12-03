#!/usr/bin/env python3
import sys


directions = {
    'N': 0,
    'E': 1,
    'S': 2,
    'W': 3
}


def result_coordinates(movements: list) -> tuple:
    x = 0
    y = 0

    direction = directions['E']
    for action, val in movements:
        if action == 'E':
            y += val
        elif action == 'W':
            y -= val
        elif action == 'N':
            x += val
        elif action == 'S':
            x -= val
        elif action == 'F':
            if direction == directions['E']:
                y += val
            elif direction == directions['W']:
                y -= val
            elif direction == directions['N']:
                x += val
            else:
                x -= val
        else:
            v = val // 90
            if action == 'L':
                direction = (direction - v) % len(directions)
            else:
                direction = (direction + v) % len(directions)

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
for sample: -8 17 25
for input: -218 -163 381
"""
