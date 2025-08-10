#!/usr/bin/env swift -enable-bare-slash-regex
import Foundation
import shared

func getCalibrationValues1(content: [String]) -> [Int] {
    return content.map { line in
        let digits =
            line
            .filter({ $0.isNumber })
            .map({ Int(String($0))! })
        return digits.first! * 10 + digits.last!
    }
}

let SPELLED_OUT_MAP: [String: String] = [
    "one": "1",
    "two": "2",
    "three": "3",
    "four": "4",
    "five": "5",
    "six": "6",
    "seven": "7",
    "eight": "8",
    "nine": "9",
]

func getCalibrationValues2(content: [String]) -> [Int] {
    return content.map { line in
        let regex1 = /one|two|three|four|five|six|seven|eight|nine/
        let first_digit =
            line
            .replacing(regex1, maxReplacements: 1) { match in
                return SPELLED_OUT_MAP[String(match.output)]!
            }
            .filter({ $0.isNumber })
            .map({ Int(String($0))! })
            .first

        let regex2 = /enin|thgie|neves|xis|evif|ruof|eerht|owt|eno/
        let last_digit =
            String(line.reversed())
            .replacing(regex2, maxReplacements: 1) { match in
                return SPELLED_OUT_MAP[String(match.output.reversed())]!
            }
            .filter({ $0.isNumber })
            .map({ Int(String($0))! })
            .first

        return first_digit! * 10 + last_digit!
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

    let calibrationValues1 = getCalibrationValues1(
        content: content.components(separatedBy: CharacterSet.newlines))
    let sum1 = calibrationValues1.reduce(0, +)
    print("Part 1: \(sum1)")

    let calibrationValues2 = getCalibrationValues2(
        content: content.components(separatedBy: CharacterSet.newlines))
    let sum2 = calibrationValues2.reduce(0, +)
    print("Part 2: \(sum2)")
}

main()
