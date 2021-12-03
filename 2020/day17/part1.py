#!/usr/bin/env python3
import sys


def parse_input(fname: str) -> set:
    active_states = set()
    with open(sys.argv[1], 'r') as f:
        for x, line in enumerate(f):
            for y, char in enumerate(line):
                if char == '#':
                    active_states.add((x, y, 0))

    return active_states


def get_neighbours(state: tuple) -> list:
    pass


def run_cycle(active_states: set) -> set:
    new_actives = active_states.copy()
    for state in active_states:
        s = sum(v in active_states for v in get_neighbours(state))
        if s == 2 or s == 3:
            new_actives.add(state)
        else:
            new_actives.remove(state)

    return new_actives


def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)

    active_states = parse_input(sys.argv[1])
    # print(active_states)

    for _ in range(6):
        active_states = run_cycle(active_states)

    print(len(active_states))



if __name__ == "__main__":
    main()

