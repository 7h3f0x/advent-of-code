#include <climits>
#include <fstream>
#include <iostream>

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

    int prev_val = INT_MAX;
    size_t count = 0;
    std::string line;
    while (getline(inp, line)) {
        int val = std::stoi(line);
        if (val > prev_val)
            count += 1;
        prev_val = val;
    }

    std::cout << count << std::endl;

    inp.close();
    return 0;
}
