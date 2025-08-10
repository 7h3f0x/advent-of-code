#!/usr/bin/env swift
import Foundation
import shared

enum Direction {
    case Up
    case Down
    case Left
    case Right
    func invert() -> Direction {
        switch self {
        case .Up:
            return .Down
        case .Down:
            return .Up
        case .Left:
            return .Right
        case .Right:
            return .Left
        }
    }
}

struct Pipe {
    let directions: (Direction, Direction)?
    init(char: Character) {
        switch char {
        case "|":
            self.directions = (.Up, .Down)
        case "-":
            self.directions = (.Left, .Right)
        case "L":
            self.directions = (.Right, .Up)
        case "J":
            self.directions = (.Left, .Up)
        case "7":
            self.directions = (.Left, .Down)
        case "F":
            self.directions = (.Right, .Down)
        default:
            self.directions = nil
        }
    }
    func getOther(_ direction: Direction) -> Direction? {
        if let (d1, d2) = self.directions {
            if d1 == direction {
                return d2
            } else if d2 == direction {
                return d1
            }
        }
        return nil
    }
    func contains(_ direction: Direction) -> Bool {
        if let (d1, d2) = self.directions {
            return d1 == direction || d2 == direction
        }
        return false
    }
}

class Tiles {
    typealias Index = (Int, Int)
    typealias Movement = (Index, Direction)
    let tiles: [[Pipe]]
    let start: Index
    init(content: String) {
        let grid = content.components(separatedBy: CharacterSet.newlines)
        var tiles = [[Pipe]]()
        var start: Index = (0, 0)
        tiles.append(Array(repeating: Pipe(char: "."), count: grid[0].count + 2))
        for (i, line) in grid.enumerated() {
            if let idx = line.firstIndex(of: "S") {
                start = (i + 1, line.distance(from: line.startIndex, to: idx) + 1)
            }
            var tile = [Pipe]()
            tile.append(Pipe(char: "."))
            tile.append(contentsOf: line.map { Pipe(char: $0) })
            tile.append(Pipe(char: "."))
            tiles.append(tile)
        }
        tiles.append(Array(repeating: Pipe(char: "."), count: grid[0].count + 2))
        self.tiles = tiles
        self.start = start
    }
    func getNext(position: (Int, Int), direction: Direction) -> Movement {
        var nextIndex: Index
        switch direction {
        case .Up:
            nextIndex = (position.0 - 1, position.1)
        case .Down:
            nextIndex = (position.0 + 1, position.1)
        case .Left:
            nextIndex = (position.0, position.1 - 1)
        case .Right:
            nextIndex = (position.0, position.1 + 1)
        }
        return (nextIndex, direction)
    }
    func getStartNeighbours() -> (Movement, Movement) {
        var neighbours = [Movement]()
        if self.tiles[self.start.0 - 1][self.start.1].contains(.Down) {
            neighbours.append(((self.start.0 - 1, self.start.1), .Up))
        }
        if self.tiles[self.start.0 + 1][self.start.1].contains(.Up) {
            neighbours.append(((self.start.0 + 1, self.start.1), .Down))
        }
        if self.tiles[self.start.0][self.start.1 - 1].contains(.Right) {
            neighbours.append(((self.start.0, self.start.1 - 1), .Left))
        }
        if self.tiles[self.start.0][self.start.1 + 1].contains(.Left) {
            neighbours.append(((self.start.0, self.start.1 + 1), .Right))
        }
        assert(neighbours.count == 2)
        return (neighbours[0], neighbours[1])
    }
    func getLoopContainingStart() -> [Index] {
        var (n1, n2) = self.getStartNeighbours()
        var indices = [Index]()
        indices.append(self.start)
        while n1.0 != n2.0 {
            let idx = n1.0
            let pipe = self.tiles[idx.0][idx.1]
            let dir = pipe.getOther(n1.1.invert())!
            n1 = self.getNext(position: idx, direction: dir)
            indices.append(idx)
        }
        return indices
    }
}

func part1(content: String) -> Int {
    let tiles = Tiles(content: content)
    return (tiles.getLoopContainingStart().count + 1) / 2
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
    // print("Part2: \(part2(content: content))")
}

main()
