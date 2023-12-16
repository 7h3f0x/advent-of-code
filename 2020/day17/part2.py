#!/usr/bin/env python3
import sys


def parse_input(fname: str) -> set:
    active_states = set()
    with open(fname, 'r') as f:
        for x, line in enumerate(f):
            for y, char in enumerate(line):
                if char == '#':
                    active_states.add((x, y, 0, 0))

    return active_states


def get_neighbours(state: tuple) -> set:
    neighbours = set()
    for x in range(state[0] - 1, state[0] + 2):
        for y in range(state[1] - 1, state[1] + 2):
            for z in range(state[2] - 1, state[2] + 2):
                for w in range(state[3] - 1, state[3] + 2):
                    neighbours.add((x, y, z, w))
    neighbours.remove(state)
    return neighbours

def run_cycle(active_states: set) -> set:
    scores = {}
    for state in active_states:
        for v in get_neighbours(state):
            scores[v] = scores.get(v, 0) + 1

    new_actives = set()
    for state, score in scores.items():
        if state in active_states and score == 2 or score == 3:
            new_actives.add(state)
        elif state not in active_states and score == 3:
            new_actives.add(state)

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

"""
for sample: 848
for input: 1908
"""

