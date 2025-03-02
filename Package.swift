// swift-tools-version:5.5
import PackageDescription

let package = Package(
    name: "OutbrainSDK",
    platforms: [
        .iOS(.v10)
    ],
    products: [
        .library(name: "OutbrainSDK", targets: ["WrapperSPMTarget"])
    ],
    dependencies: [
        // Here we define our package's external dependencies
        // and from where they can be fetched:
    ],
    targets: [
        .binaryTarget(
            name: "OutbrainSDKXCFramework",
            path: "OutbrainSDK.xcframework"
        ),
        .target(
            name: "WrapperSPMTarget",
            dependencies: [
                .target(name: "OutbrainSDKXCFramework", condition: .when(platforms: .some([.iOS])))
            ]
        )
    ]
)
