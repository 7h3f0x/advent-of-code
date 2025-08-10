#!/usr/bin/env swift

import Foundation
import shared

struct RangeMap {
    let ranges: [(Range<Int>, Int)]
    init(ranges: [(Range<Int>, Int)]) {
        self.ranges = ranges
    }
    init(lines: [String]) {
        ranges =
            lines
            .map { $0.split(separator: " ").map { Int($0)! } }
            .map { ($0[1]..<($0[1] + $0[2]), $0[0]) }
    }
    func get(_ idx: Int) -> Int {
        for (range, value) in ranges {
            if range.contains(idx) {
                return value + idx - range.lowerBound
            }
        }
        return idx
    }
    func get(_ ranges: [Range<Int>]) -> [Range<Int>] {
        var ranges = ranges
        var outRanges = [Range<Int>]()
        while let inRange = ranges.popLast() {
            var matched = false
            for (range, offset) in self.ranges {
                let intersection = inRange.clamped(to: range)
                let intersectionStart = intersection.lowerBound
                let intersectionEnd = intersection.upperBound
                if intersection.count > 0 {
                    outRanges.append(
                        intersectionStart + offset - range.lowerBound..<intersectionEnd + offset
                            - range.lowerBound)
                    matched = true
                    if intersectionStart > inRange.lowerBound {
                        ranges.append(inRange.lowerBound..<intersectionStart)
                    }
                    if intersectionEnd < inRange.upperBound {
                        ranges.append(intersectionEnd..<inRange.upperBound)
                    }
                    break
                }
            }
            if !matched {
                outRanges.append(inRange)
            }
        }
        return outRanges
    }
}

extension Int {
    func apply(_ rangeMap: RangeMap) -> Int {
        return rangeMap.get(self)
    }
}

extension [Range<Int>] {
    func apply(_ rangeMap: RangeMap) -> [Range<Int>] {
        return rangeMap.get(self)
    }
}

class Almanac {
    let seeds: [Int]
    let seedToSoilMap: RangeMap
    let soilToFertilizerMap: RangeMap
    let fertilizerToWaterMap: RangeMap
    let waterToLightMap: RangeMap
    let lightToTemperatureMap: RangeMap
    let temperatureToHumidityMap: RangeMap
    let humidityToLocationMap: RangeMap
    init(content: String) {
        let parts = content.split(separator: "\n\n")
        seeds =
            parts[0]
            .split(separator: ": ")[1]
            .split(separator: " ")
            .map { Int($0)! }
        seedToSoilMap = RangeMap(
            lines: Array(parts[1].components(separatedBy: CharacterSet.newlines)[1...])
        )
        soilToFertilizerMap = RangeMap(
            lines: Array(parts[2].components(separatedBy: CharacterSet.newlines)[1...])
        )
        fertilizerToWaterMap = RangeMap(
            lines: Array(parts[3].components(separatedBy: CharacterSet.newlines)[1...])
        )
        waterToLightMap = RangeMap(
            lines: Array(parts[4].components(separatedBy: CharacterSet.newlines)[1...])
        )
        lightToTemperatureMap = RangeMap(
            lines: Array(parts[5].components(separatedBy: CharacterSet.newlines)[1...])
        )
        temperatureToHumidityMap = RangeMap(
            lines: Array(parts[6].components(separatedBy: CharacterSet.newlines)[1...])
        )
        humidityToLocationMap = RangeMap(
            lines: Array(parts[7].components(separatedBy: CharacterSet.newlines)[1...])
        )
    }
    func getLocation(for seed: Int) -> Int {
        return
            seed
            .apply(seedToSoilMap)
            .apply(soilToFertilizerMap)
            .apply(fertilizerToWaterMap)
            .apply(waterToLightMap)
            .apply(lightToTemperatureMap)
            .apply(temperatureToHumidityMap)
            .apply(humidityToLocationMap)
    }
    func getLocations1() -> [Int] {
        return seeds.map { getLocation(for: $0) }
    }
    func getLocations2() -> [Range<Int>] {
        var seedRanges: [Range<Int>] = []
        for (start, length) in sequence(
            state: seeds.makeIterator(),
            next: { it in
                it.next().map { ($0, it.next()!) }
            })
        {
            seedRanges.append(start..<start + length)
        }
        return
            seedRanges
            .apply(seedToSoilMap)
            .apply(soilToFertilizerMap)
            .apply(fertilizerToWaterMap)
            .apply(waterToLightMap)
            .apply(lightToTemperatureMap)
            .apply(temperatureToHumidityMap)
            .apply(humidityToLocationMap)
    }
}

func part1(content: String) -> Int {
    let alamanac = Almanac(content: content)
    return alamanac.getLocations1().min()!
}

func part2(content: String) -> Int {
    let alamanac = Almanac(content: content)
    return alamanac.getLocations2().map { $0.lowerBound }.min()!
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
