#include <fstream>
#include <iostream>
#include <vector>

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
    std::vector<size_t> count_1;
    size_t num_lines = 0;
    while (getline(inp, line)) {
        num_lines += 1;
        if (count_1.size() == 0) {
            count_1 = std::vector<size_t>(line.length(), 0);
        }
        for (int i = 0; i < line.length(); ++i) {
            char ch = line[i];
            if (ch == '1')
                count_1[i] += 1;
        }
    }

    size_t gamma_rate = 0, epsilon_rate = 0;
    for (auto num : count_1) {
        gamma_rate <<= 1;
        epsilon_rate <<= 1;
        if (num <= num_lines / 2) {
            // 1 is less common
            epsilon_rate += 1;
        } else {
            gamma_rate += 1;
        }
    }

    std::cout << gamma_rate * epsilon_rate << std::endl;

    inp.close();
    return 0;
}
