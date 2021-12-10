#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class Decoder {
  private:
    static constexpr size_t OUTPUT_SIZE = 4;
    std::vector<std::string> output;
    std::unordered_map<size_t, int> length_map;

    static std::vector<std::string> split(const std::string &line, char ch) {
        std::vector<std::string> ret;

        std::stringstream ss(line);
        std::string tmp;
        while (getline(ss, tmp, ch))
            ret.push_back(tmp);

        return ret;
    }

    static void parse_error(const std::string &line) {
        std::cerr << "Unable to parse line: " << line << std::endl;
        exit(1);
    }

  public:
    Decoder(const std::string &line) {
        int idx = line.find(" | ");
        if (idx == std::string::npos)
            parse_error(line);

        output = split(line.substr(idx + 3), ' ');
        if (output.size() != OUTPUT_SIZE)
            parse_error(line);

        length_map = {{2, 1}, {4, 4}, {3, 7}, {7, 8}};
    }

    std::vector<int> get_values() {
        std::vector<int> ret;
        for (auto &str : output) {
            size_t len = str.length();
            if (length_map.find(len) != length_map.end()) {
                ret.push_back(length_map[len]);
            }
        }

        return ret;
    }
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << (argc < 1 ? "./solve" : argv[0])
                  << " <input file>" << std::endl;
        return 1;
    }

    std::ifstream inp;
    inp.open(argv[1]);
    if (!inp.is_open()) {
        std::cerr << "Unable to open file: " << argv[1] << std::endl;
        return 2;
    }

    std::string line;
    unsigned long long count = 0;
    while (getline(inp, line)) {
        Decoder dec(line);
        count += dec.get_values().size();
    }

    std::cout << count << std::endl;

    inp.close();
    return 0;
}
