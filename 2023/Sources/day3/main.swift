#!/usr/bin/env swift

import Foundation
import shared

func getNeighbourIndices(matrix: [String], i: Int, s_idx: Int, e_idx: Int) -> [(Int, Int)] {
    var result: [(Int, Int)] = []
    var s_idx = s_idx
    if s_idx > 0 {
        s_idx -= 1
        result.append((i, s_idx))
    }
    var e_idx = e_idx
    if e_idx < matrix[0].count - 1 {
        e_idx += 1
        result.append((i, e_idx))
    }
    if i > 1 {
        for num in s_idx...e_idx {
            result.append((i - 1, num))
        }
    }
    if i < matrix.count - 1 {
        for num in s_idx...e_idx {
            result.append((i + 1, num))
        }
    }
    return result
}

func checkRange(matrix: [String], i: Int, s_idx: Int, e_idx: Int) -> Bool {
    let indices = getNeighbourIndices(matrix: matrix, i: i, s_idx: s_idx, e_idx: e_idx).filter {
        (i, j) in
        let e_idx = matrix[i].index(matrix[i].startIndex, offsetBy: j)
        return (!matrix[i][e_idx].isNumber) && matrix[i][e_idx] != "."
    }
    return indices.count != 0
}

func part1(content: String) -> Int {
    var result = 0
    let matrix = content.components(separatedBy: CharacterSet.newlines)
    for (i, line) in matrix.enumerated() {
        var temp = 0
        var s_idx = -1
        var e_idx = -1
        for (j, char) in line.enumerated() {
            if char.isNumber {
                if s_idx == -1 {
                    s_idx = j
                }
                e_idx = j
                temp *= 10
                temp += Int(String(char))!
            } else {
                if s_idx != -1 {
                    if checkRange(matrix: matrix, i: i, s_idx: s_idx, e_idx: e_idx) {
                        result += temp
                    }
                    temp = 0
                    s_idx = -1
                    e_idx = -1
                }
            }
        }
        if s_idx != -1 {
            if checkRange(matrix: matrix, i: i, s_idx: s_idx, e_idx: e_idx) {
                result += temp
            }
        }
    }
    return result
}

func getNeighbourValues(matrix: [String], i: Int, j: String.Index) -> [Int] {
    var result: [Int] = []
    // left
    if j > matrix[i].startIndex && matrix[i][matrix[i].index(before: j)].isNumber {
        var s_idx = matrix[i][matrix[i].startIndex..<j].lastIndex { !$0.isNumber }
        s_idx = s_idx != nil ? matrix[i].index(after: s_idx!) : matrix[i].startIndex
        result.append(Int(matrix[i][s_idx!..<j])!)
    }
    // right
    if j < matrix[i].index(before: matrix[i].endIndex)
        && matrix[i][matrix[i].index(after: j)].isNumber
    {
        var e_idx =
            matrix[i][matrix[i].index(after: j)..<matrix[i].endIndex]
            .firstIndex { !$0.isNumber }
        e_idx = e_idx ?? matrix[i].endIndex
        result.append(Int(matrix[i][matrix[i].index(after: j)..<e_idx!])!)
    }

    // top and below row
    for idx in [i - 1, i + 1] {
        if matrix[idx][j].isNumber {
            var s_idx = matrix[idx][matrix[idx].startIndex...j].lastIndex { !$0.isNumber }
            s_idx = s_idx != nil ? matrix[idx].index(after: s_idx!) : matrix[idx].startIndex
            let e_idx = matrix[idx][j..<matrix[i].endIndex].firstIndex { !$0.isNumber }!
            result.append(Int(matrix[idx][s_idx!..<e_idx])!)
        } else {
            // left
            if j > matrix[idx].startIndex && matrix[idx][matrix[idx].index(before: j)].isNumber {
                var s_idx = matrix[idx][matrix[idx].startIndex..<j].lastIndex { !$0.isNumber }
                s_idx = s_idx != nil ? matrix[idx].index(after: s_idx!) : matrix[idx].startIndex
                result.append(Int(matrix[idx][s_idx!..<j])!)
            }
            // right
            if j < matrix[idx].index(before: matrix[idx].endIndex)
                && matrix[idx][matrix[idx].index(after: j)].isNumber
            {
                var e_idx =
                    matrix[idx][matrix[i].index(after: j)..<matrix[idx].endIndex]
                    .firstIndex { !$0.isNumber }
                e_idx = e_idx ?? matrix[idx].endIndex
                result.append(Int(matrix[idx][matrix[idx].index(after: j)..<e_idx!])!)
            }
        }
    }
    return result
}

func part2(content: String) -> Int {
    var result = 0
    let matrix = content.components(separatedBy: CharacterSet.newlines)
    for (idx, line) in matrix.enumerated() {
        for (j, char) in line.enumerated() {
            if char != "*" {
                continue
            }
            let j_idx = line.index(line.startIndex, offsetBy: j)
            let vals = getNeighbourValues(matrix: matrix, i: idx, j: j_idx)
            if vals.count == 2 {
                result += vals.reduce(1, *)
            }
        }
    }
    return result
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
