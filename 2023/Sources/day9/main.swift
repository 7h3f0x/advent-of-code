#!/usr/bin/env swift
import Foundation
import shared

class Sequence {
    var layers: [[Int]]
    init(line: String) {
        layers = []
        var sequence = line.split(separator: " ").compactMap { Int($0) }
        while !sequence.allSatisfy({ $0 == 0 }) {
            layers.append(sequence)
            var newSequence: [Int] = []
            for (prev, next) in zip(sequence, sequence.dropFirst()) {
                newSequence.append(next - prev)
            }
            sequence = newSequence
        }
    }
    func next() -> Int {
        var idx = layers.index(before: layers.endIndex)
        var value = layers[idx].last!
        while idx != layers.startIndex {
            idx = layers.index(before: idx)
            value += layers[idx].last!
        }
        return value
    }
    func prev() -> Int {
        var idx = layers.index(before: layers.endIndex)
        var value = layers[idx].first!
        while idx != layers.startIndex {
            idx = layers.index(before: idx)
            value = layers[idx].first! - value
        }
        return value
    }
}

func part1(content: String) -> Int {
    let sequences = content.components(separatedBy: CharacterSet.newlines).map {
        Sequence(line: $0)
    }
    return sequences.map { $0.next() }.reduce(0, +)
}

func part2(content: String) -> Int {
    let sequences = content.components(separatedBy: CharacterSet.newlines).map {
        Sequence(line: $0)
    }
    return sequences.map { $0.prev() }.reduce(0, +)
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
