#!/usr/bin/env python3
import sys
import math


def parse_input(fname: str) -> tuple:
    with open(sys.argv[1], 'r') as f:
        l1, l2 = f.read().splitlines()
        earliest_timestamp = int(l1)
        bus_ids = list()
        for bus_id in l2.split(","):
            if bus_id != 'x':
                bus_ids.append(int(bus_id))

    return earliest_timestamp, bus_ids


def find_earliest(earliest_timestamp: int, bus_ids: list) -> tuple:
    gap = math.inf
    chosen_bus_id = None
    for bus_id in bus_ids:
        m = math.ceil(earliest_timestamp / bus_id) * bus_id
        time_rem = m - earliest_timestamp
        if time_rem < gap:
            gap = time_rem
            chosen_bus_id = bus_id

    return chosen_bus_id, gap


def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)

    earliest_timestamp, bus_ids = parse_input(sys.argv[1])

    chosen_bus_id, time_rem = find_earliest(earliest_timestamp, bus_ids)

    print(f"{chosen_bus_id}, {time_rem} => {chosen_bus_id * time_rem}")


if __name__ == "__main__":
    main()

"""
for sample: 59, 5 => 295
for input: 17 , 6 => 102
"""
