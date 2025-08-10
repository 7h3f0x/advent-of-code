#!/usr/bin/env swift

import Foundation
import shared

class Card {
    let id: Int
    let winningNumbers: [Int]
    let cardNumbers: [Int]
    init(line: String) {
        let parts = line.split(separator: ": ")
        id = Int(String(parts[0].split(separator: " ")[1]))!
        let numbersParts = parts[1].split(separator: " | ")
        winningNumbers =
            numbersParts[0]
            .components(separatedBy: CharacterSet.whitespaces)
            .compactMap { Int($0) }
        cardNumbers =
            numbersParts[1]
            .components(separatedBy: CharacterSet.whitespaces)
            .compactMap { Int($0) }
    }
    static func cardsFrom(content: String) -> [Card] {
        return content.components(separatedBy: CharacterSet.newlines).map {
            Card(line: $0)
        }
    }
    func numberOfWins() -> Int {
        return
            cardNumbers
            .filter { winningNumbers.contains($0) }
            .count
    }
    func points() -> Int {
        let numWins = numberOfWins()
        return numWins != 0 ? (1 << (numWins - 1)) : 0
    }
}

func part1(content: String) -> Int {
    let cards = Card.cardsFrom(content: content)
    return cards.map { $0.points() }.reduce(0, +)
}

func part2(content: String) -> Int {
    let cards = Card.cardsFrom(content: content)
    var numCards = Array(repeating: 1, count: cards.count)
    for idx in 0..<(numCards.count - 1) {
        let wins = cards[idx].numberOfWins()
        if wins == 0 {
            continue
        }
        var end = idx + wins
        if end >= numCards.count {
            end = numCards.count - 1
        }
        for idx2 in idx + 1...end {
            numCards[idx2] += numCards[idx]
        }
    }
    return numCards.reduce(0, +)
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
