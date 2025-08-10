#!/usr/bin/env swift
import Foundation
import shared

enum HandType: Int {
    case highCard
    case pair
    case twoPairs
    case threeOfAKind
    case fullHouse
    case fourOfAKind
    case fiveOfAKind
}

enum Card: Int {
    case two
    case three
    case four
    case five
    case six
    case seven
    case eight
    case nine
    case ten
    case jack
    case queen
    case king
    case ace
    init?(from char: String.Element) {
        switch char {
        case "2": self = .two
        case "3": self = .three
        case "4": self = .four
        case "5": self = .five
        case "6": self = .six
        case "7": self = .seven
        case "8": self = .eight
        case "9": self = .nine
        case "T": self = .ten
        case "J": self = .jack
        case "Q": self = .queen
        case "K": self = .king
        case "A": self = .ace
        default: return nil
        }
    }
}

struct Hand {
    let cards: [Card]
    let bid: Int
    let isJokerWildCard: Bool
    init(line: String, isJokerWildCard: Bool = false) {
        self.isJokerWildCard = isJokerWildCard
        let parts = line.split(separator: " ")
        bid = Int(parts[1])!
        cards = parts[0].map { Card(from: $0)! }
    }
    var type: HandType {
        var counts = cards.reduce(into: [:]) { counts, card in counts[card, default: 0] += 1 }
        let jokerCount = counts[.jack, default: 0]
        var values: [Int]
        if isJokerWildCard && jokerCount != 5 {
            counts[.jack] = nil
            values = counts.values.sorted()
            let value = values.popLast()!
            values.append(value + jokerCount)
        } else {
            values = counts.values.sorted()
        }
        switch values {
        case [5]: return .fiveOfAKind
        case [1, 4]: return .fourOfAKind
        case [2, 3]: return .fullHouse
        case [1, 1, 3]: return .threeOfAKind
        case [1, 2, 2]: return .twoPairs
        case [1, 1, 1, 2]: return .pair
        default: return .highCard
        }
    }
    static func < (lhs: Hand, rhs: Hand) -> Bool {
        if lhs.type.rawValue < rhs.type.rawValue {
            return true
        } else if lhs.type.rawValue > rhs.type.rawValue {
            return false
        } else {
            for (c1, c2) in zip(lhs.cards, rhs.cards) {
                if c1 == c2 {
                    continue
                }
                if lhs.isJokerWildCard && c1 == .jack {
                    return true
                }
                if rhs.isJokerWildCard && c2 == .jack {
                    return false
                }
                if c1.rawValue > c2.rawValue {
                    return false
                } else if c1.rawValue < c2.rawValue {
                    return true
                }
            }
            return false
        }
    }
}

func part1(content: String) -> Int {
    var hands = content.components(separatedBy: CharacterSet.newlines).map { Hand(line: $0) }
    hands.sort { $0 < $1 }
    return hands.enumerated().reduce(0) { sum, hand in
        return sum + (hand.element.bid * (hand.offset + 1))
    }
}

func part2(content: String) -> Int {
    var hands = content.components(separatedBy: CharacterSet.newlines).map {
        Hand(line: $0, isJokerWildCard: true)
    }
    hands.sort { $0 < $1 }
    return hands.enumerated().reduce(0) { sum, hand in
        // print(hand.element.bid, hand.element.cards, hand.element.type, hand.offset + 1)
        return sum + (hand.element.bid * (hand.offset + 1))
    }
}

func main() {
    guard CommandLine.arguments.count > 1 else {
        print("Please provide a filename as a command-line argument.")
        return
    }

    let filename = CommandLine.arguments[1]

    guard let content = Utils.readFile(filename: filename) else {
        print("Unable to read input file")
        return
    }
    print("Part1: \(part1(content: content))")
    print("Part2: \(part2(content: content))")
}

main()
