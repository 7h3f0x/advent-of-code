#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

void parse_error(const std::string &line) {
    std::cerr << "Unable to parse line: " << line << std::endl;
    exit(1);
}

std::vector<std::string> split(const std::string &line, char ch) {
    std::vector<std::string> ret;

    std::stringstream ss(line);
    std::string tmp;
    while (getline(ss, tmp, ch))
        ret.push_back(tmp);

    return ret;
}

class Decoder {
  private:
    std::unordered_map<int, int> signal_map;
    std::unordered_map<int, int> length_map = {{2, 1}, {4, 4}, {3, 7}, {7, 8}};

    // convert strings of the form `abcd` to a number which has it's 1st, 2nd,
    // 3rd and 4th bits set. i.e. for every character `x` at a distance `i` from
    // `a`, it is represented in this bitmap representation by setting the ith
    // bit to 1
    static int flatten(const std::string &line) {
        int val = 0;
        for (auto ch : line) {
            val |= 1 << (ch - 'a');
        }

        return val;
    }

    // checks if all bits set in a2 are also set in a1 or not
    static bool is_subset(int a1, int a2) {
        while (a2) {
            if (a2 & 1) {
                if ((a1 & 1) == 0) {
                    return false;
                }
            }
            a1 >>= 1;
            a2 >>= 1;
        }
        return true;
    }

  public:
    static constexpr size_t SIGNAL_PATTERNS_SIZE = 10;
    Decoder(std::vector<std::string> &signal_patterns) {
        std::vector<int> map_5;
        std::vector<int> map_6;

        int digit_map[10];

        for (auto &pat : signal_patterns) {
            if (length_map.find(pat.size()) != length_map.end()) {
                signal_map[flatten(pat)] = length_map[pat.size()];
                digit_map[length_map[pat.size()]] = flatten(pat);
            } else if (pat.size() == 5) {
                map_5.push_back(flatten(pat));
            } else if (pat.size() == 6) {
                map_6.push_back(flatten(pat));
            }
        }

        for (auto elem : map_6) {
            if (is_subset(elem, digit_map[4])) {
                digit_map[9] = elem;
                signal_map[elem] = 9;
            } else if (is_subset(elem, digit_map[1])) {
                digit_map[0] = elem;
                signal_map[elem] = 0;
            } else {
                digit_map[6] = elem;
                signal_map[elem] = 6;
            }
        }

        for (auto elem : map_5) {
            if (is_subset(elem, digit_map[7])) {
                digit_map[3] = elem;
                signal_map[elem] = 3;
            } else if (is_subset(digit_map[6], elem)) {
                digit_map[5] = elem;
                signal_map[elem] = 5;
            } else {
                digit_map[2] = elem;
                signal_map[elem] = 2;
            }
        }
    }

    unsigned long long decode(std::vector<std::string> &output) {
        unsigned long long val = 0;

        for (auto &str : output) {
            val *= 10;
            val += signal_map[flatten(str)];
        }

        return val;
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
    unsigned long long output_sum = 0;
    std::vector<std::string> signal_patterns;
    std::vector<std::string> output;
    while (getline(inp, line)) {
        int idx = line.find(" | ");
        if (idx == std::string::npos)
            parse_error(line);

        signal_patterns = split(line.substr(0, idx), ' ');
        if (signal_patterns.size() != Decoder::SIGNAL_PATTERNS_SIZE)
            parse_error(line);

        output = split(line.substr(idx + 3), ' ');

        Decoder dec(signal_patterns);
        output_sum += dec.decode(output);
    }

    std::cout << output_sum << std::endl;

    inp.close();
    return 0;
}
