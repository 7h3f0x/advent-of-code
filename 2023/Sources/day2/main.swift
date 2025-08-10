#!/usr/bin/env swift

import Foundation
import shared

struct Cubes {
    var red: Int = 0
    var green: Int = 0
    var blue: Int = 0
    init(line: String) {
        let parts = line.split(separator: ", ")
        parts.forEach { part in
            let parts = part.split(separator: " ")
            switch parts[1] {
            case "red":
                red = Int(parts[0])!
            case "green":
                green = Int(parts[0])!
            case "blue":
                blue = Int(parts[0])!
            default:
                break
            }
        }
    }
    init(red: Int, green: Int, blue: Int) {
        self.red = red
        self.green = green
        self.blue = blue
    }
    func contains(_ other: Cubes) -> Bool {
        return red >= other.red && blue >= other.blue && green >= other.green
    }
    static func setOfCubesFrom(content: String) -> [Cubes] {
        return content.split(separator: "; ").map { Cubes(line: String($0)) }
    }
    func power() -> Int {
        return red * green * blue
    }
}

class Game {
    let id: Int
    let cubeSet: [Cubes]
    init(line: String) {
        let parts = line.split(separator: ": ")
        id = Int(parts[0].split(separator: " ")[1])!
        cubeSet = Cubes.setOfCubesFrom(content: String(parts[1]))
    }
    func isSatisfied(by cubes: Cubes) -> Bool {
        return cubeSet.allSatisfy { cubes.contains($0) }
    }
    static func gamesFrom(content: String) -> [Game] {
        return content.components(separatedBy: CharacterSet.newlines).map { Game(line: $0) }
    }
    func minSatistiableCubes() -> Cubes {
        let maxRed = cubeSet.map { $0.red }.max()!
        let maxGreen = cubeSet.map { $0.green }.max()!
        let maxBlue = cubeSet.map { $0.blue }.max()!
        return Cubes(red: maxRed, green: maxGreen, blue: maxBlue)
    }
}

func part1(content: String) -> Int {
    let totalCubes = Cubes(red: 12, green: 13, blue: 14)
    let games = Game.gamesFrom(content: content)
    return
        games
        .filter { $0.isSatisfied(by: totalCubes) }
        .reduce(0, { $0 + $1.id })
}

func part2(content: String) -> Int {
    let games = Game.gamesFrom(content: content)
    return
        games
        .map { $0.minSatistiableCubes().power() }
        .reduce(0, +)
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
