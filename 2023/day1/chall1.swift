#!/usr/bin/env swift
import Foundation

func readFile(filename: String) -> String? {
    let path = FileManager.default.currentDirectoryPath.appending("/" + filename)
    let url = URL(fileURLWithPath: path)
    guard let data = try? Data(contentsOf: url) else {
        return nil
    }
    return String(data: data, encoding: .utf8)
}

func getCalibrationValues(content: [String]) -> [Int] {
    return content.map { line in
        let digits =
            line
            .filter({ $0.isNumber })
            .map({ Int(String($0))! })
        return digits.first! * 10 + digits.last!
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
sample1: 142
input: 56506
*/
