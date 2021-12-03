#!/usr/bin/env python3
import sys
import re


# def parse_input(input: list) -> dict:
#     all_bags = {}
#     for line in input:
#         tokens = line.split(" contain ")
#         bag_type = tokens[0][:-5]
#         bags = tokens[1].strip(".").split(", ")

#         tmp = {}
#         if bags[0] == "no other bags":
#             pass
#         else:
#             for i, bag in enumerate(bags):
#                 b = bag.split(" ")
#                 tmp[' '.join(b[1:3])] = int(b[0])

#         all_bags[bag_type] = tmp
#     return all_bags


def parse_input(input: list) -> dict:
    all_bags = {}
    for line in input:
        bag_type, bags = re.findall(r"^([\w\s]+) bags contain (.*)\.$", line)[0]
        bags = re.findall(r"(\d+) ([\w\s]+) bags?", bags)
        if not bags:
            bags = {}
        else:
            bags = {y:int(x) for x,y in bags}
        all_bags[bag_type] = bags
    return all_bags


def get_bags(all_bags: dict, match_bag: str) -> set:
    ans = set()
    prev = [match_bag]
    while True:
        curr = []
        for bag in all_bags:
            if any(p in all_bags[bag] for p in prev):
                curr.append(bag)
                ans.add(bag)
        if not curr:
            break
        prev = curr
    return ans


def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)
    with open(sys.argv[1], 'r') as f:
        input = f.read().splitlines()

    all_bags = parse_input(input)

    ans = get_bags(all_bags, "shiny gold")
    print(len(ans))

if __name__ == "__main__":
    main()

"""
for sample: 4
for input: 372
"""
