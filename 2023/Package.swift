// swift-tools-version: 5.9
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "aoc",
    platforms: [
        .macOS(.v13)
    ],
    products: [
        .executable(name: "day2", targets: ["day2"]),
        .executable(name: "day1", targets: ["day1"]),
    ],
    targets: [
        // Targets are the basic building blocks of a package, defining a module or a test suite.
        // Targets can depend on other targets in this package and products from dependencies.
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