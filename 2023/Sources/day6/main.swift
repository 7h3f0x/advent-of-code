#!/usr/bin/env swift

import Foundation
import shared

class Races {
    let times: [Int]
    let distances: [Int]
    init(content: String) {
        let lines = content.components(separatedBy: CharacterSet.newlines)
        times = lines[0].split(separator: " ").compactMap { Int($0) }
        distances = lines[1].split(separator: " ").compactMap { Int($0) }
    }
    func winPossibilitiesForRace(time: Int, distance: Int) -> Int {
        let discriminant = pow(Double(time), 2) - (4 * Double(distance))
        let smaller = (Double(time) - sqrt(discriminant)) / 2
        let larger = (Double(time) + sqrt(discriminant)) / 2
        return Int(ceil(larger) - 1) - Int(floor(smaller) + 1) + 1
    }
    func winPossibilities() -> [Int] {
        return zip(times, distances).map { winPossibilitiesForRace(time: $0, distance: $1) }
    }
}

/*
x = hold time = speed
t - x = time available to race

x(t - x) > d
xt - x^2 -d > 0

find roots of   - x^2 + xt -d = 0
x^2 - xt + d = 0
x = (t +- sqrt(t^2 - 4d)) / 2
*/

func part1(content: String) -> Int {
    let races = Races(content: content)
    return races.winPossibilities().reduce(1, *)
}

func part2(content: String) -> Int {
    let races = Races(content: content)
    let time = races.times.reduce(0) {
        let digits = Double(String($1).count)
        return ($0 * Int(pow(Double(10), digits))) + $1
    }
    let distance = races.distances.reduce(0) {
        let digits = Double(String($1).count)
        return ($0 * Int(pow(Double(10), digits))) + $1
    }
    return races.winPossibilitiesForRace(time: time, distance: distance)
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
