import Foundation

public class Utils {
    public static func readFile(filename: String) -> String? {
        let path = FileManager.default.currentDirectoryPath.appending("/" + filename)
        let url = URL(fileURLWithPath: path)
        guard let data = try? Data(contentsOf: url) else {
            return nil
        }
        return String(data: data, encoding: .utf8)
    }
}
