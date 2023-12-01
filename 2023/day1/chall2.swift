#!/usr/bin/env swift -enable-bare-slash-regex
import Foundation

func readFile(filename: String) -> String? {
    let path = FileManager.default.currentDirectoryPath.appending("/" + filename)
    let url = URL(fileURLWithPath: path)
    guard let data = try? Data(contentsOf: url) else {
        return nil
    }
    return String(data: data, encoding: .utf8)
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

func getCalibrationValues(content: [String]) -> [Int] {
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

    guard let content = readFile(filename: filename) else {
        print("Unable to read input file")
        return
    }

    let calibrationValues = getCalibrationValues(
        content: content.components(separatedBy: CharacterSet.newlines))
    let sum = calibrationValues.reduce(0, +)
    print(sum)
}

main()
/*
sample2: 281
input: 56017
*/
