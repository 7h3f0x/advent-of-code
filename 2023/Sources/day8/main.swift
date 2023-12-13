#!/usr/bin/env swift
import Foundation
import shared

func gcd(_ a: Int, _ b: Int) -> Int {
    var a = a
    var b = b
    while b != 0 {
        let t = b
        b = a % b
        a = t
    }
    return a
}

func lcm(_ a: Int, _ b: Int) -> Int {
    a * b / gcd(a, b)
}

class Network {
    let instruction: String
    let nodeMap: [String: (String, String)]
    init(content: String) {
        let parts = content.split(separator: "\n\n")
        instruction = String(parts[0])
        nodeMap = parts[1].components(separatedBy: CharacterSet.newlines).map { line in
            var line = line
            line.removeLast()
            let parts = line.split(separator: " = (")
            let inNode = String(parts[0])
            let outNodes = parts[1].split(separator: ", ").map { String($0) }
            return (inNode, (outNodes[0], outNodes[1]))
        }.reduce(into: [String: (String, String)]()) { (result, node) in
            result[node.0] = node.1
        }
    }
    func getNext(from node: String, instr: Character) -> String {
        switch instr {
        case "R":
            return nodeMap[node]!.1
        case "L":
            return nodeMap[node]!.0
        default:
            return node
        }
    }
    func numberOfSteps(from start: String, to end: String) -> Int {
        var current = start
        var numSteps = 0
        while current != end {
            for instr in instruction {
                current = getNext(from: current, instr: instr)
                numSteps += 1
                if current == end {
                    return numSteps
                }
            }
        }
        return numSteps
    }
    func numberOfStepsForGhost(from start: String) -> Int {
        var current = start
        var numSteps = 0
        while numSteps == 0 || current.last != "Z" {
            for instr in instruction {
                current = getNext(from: current, instr: instr)
                numSteps += 1
                if current.last == "Z" {
                    return numSteps
                }
            }
        }
        assert(numSteps % instruction.count == 0)
        assert(numSteps == numberOfStepsForGhost(from: current))
        return numSteps
    }
    func getStartingForGhost() -> [String] {
        return nodeMap.compactMap { $0.key.last == "A" ? $0.key : nil }
    }
    func numberOfStepsForGhost() -> Int {
        getStartingForGhost().map { numberOfStepsForGhost(from: $0) }.reduce(1, lcm)
    }
}

func part1(content: String) -> Int {
    let network = Network(content: content)
    return network.numberOfSteps(from: "AAA", to: "ZZZ")
}

// https://www.youtube.com/watch?v=_nnxLcrwO_U
func part2(content: String) -> Int {
    let network = Network(content: content)
    return network.numberOfStepsForGhost()
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
