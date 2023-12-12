// swift-tools-version: 5.9
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "aoc",
    platforms: [
        .macOS(.v13)
    ],
    products: [
        .executable(name: "day8", targets: ["day8"]),
        .executable(name: "day7", targets: ["day7"]),
        .executable(name: "day6", targets: ["day6"]),
        .executable(name: "day5", targets: ["day5"]),
        .executable(name: "day4", targets: ["day4"]),
        .executable(name: "day3", targets: ["day3"]),
        .executable(name: "day2", targets: ["day2"]),
        .executable(name: "day1", targets: ["day1"]),
    ],
    targets: [
        // Targets are the basic building blocks of a package, defining a module or a test suite.
        // Targets can depend on other targets in this package and products from dependencies.
        .executableTarget(
            name: "day8",
            dependencies: ["shared"]
        ),
        .executableTarget(
            name: "day7",
            dependencies: ["shared"]
        ),
        .executableTarget(
            name: "day6",
            dependencies: ["shared"]
        ),
        .executableTarget(
            name: "day5",
            dependencies: ["shared"]
        ),
        .executableTarget(
            name: "day4",
            dependencies: ["shared"]
        ),
        .executableTarget(
            name: "day3",
            dependencies: ["shared"]
        ),
        .executableTarget(
            name: "day2",
            dependencies: ["shared"]
        ),
        .executableTarget(
            name: "day1",
            dependencies: ["shared"]
        ),
        .target(
            name: "shared"
        ),
    ]
)

for target in package.targets {
    target.swiftSettings = target.swiftSettings ?? []
    target.swiftSettings?.append(
        .unsafeFlags([
            "-enable-bare-slash-regex"
        ])
    )
}
