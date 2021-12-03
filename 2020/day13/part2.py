#!/usr/bin/env python3
import sys


def parse_input(fname: str) -> list:
    with open(sys.argv[1], 'r') as f:
        _, l2 = f.read().splitlines()
        bus_ids = list()
        for idx, bus_id in enumerate(l2.split(",")):
            if bus_id != 'x':
                bus_id = int(bus_id)
                # since, t + idx = bus_id * n => t % bus_id =  (-idx) % bus_id
                bus_ids.append(( (-idx) % bus_id , bus_id))

    return bus_ids


def extended_gcd(a: int, b: int) -> tuple:
    """
    d = ax + by = bx1 + (a % b)y1
    => ax + by = bx1 + (a - (a//b)*b)y1
    ax + by = bx1 + ay1 - (a//b)*y1* b
    ax + by = a(y1) + b(x1 - (a//b)*y1)
    => x = y1, y = x1 - (a//b)*y1
    """
    assert a >= b, "parameters for `extended_gcd` must be such that a >= b"
    if b == 0:
        return a, 1, 0
    else:
        d1, x1, y1 = extended_gcd(b, a % b)
        return d1, y1, x1 - (a // b) * y1


def mod_inverse(a: int, n: int) -> int:
    """
    returns modular inverse of a with n
    """
    d, x, y = extended_gcd(a, n)
    # a, n need to be co-prime for this to work
    assert d == 1, f"Unable to find mod-inverse for {a}, {n}"
    return x


def chinese_remainder_theorem(equations: list) -> tuple:
    """
    equations is list of the form -> [(remainder, divisor) , ... ]
    """
    N = 1
    for _, n in equations:
        N *= n

    min_ans = 0
    for rem, n in equations:
        m = N // n
        min_ans += m * mod_inverse(m, n) * rem

    min_ans %= N

    return N, min_ans


def main():
    if len(sys.argv) < 2:
        print(f"usage: {sys.argv[0]} <input-fname>", file=sys.stderr)
        sys.exit(1)

    bus_ids = parse_input(sys.argv[1])
    # print(bus_ids)
    _, min_t = chinese_remainder_theorem(bus_ids)
    print(min_t)


if __name__ == "__main__":
    main()

"""
for sample: 1068781
for input: 327300950120029
"""
