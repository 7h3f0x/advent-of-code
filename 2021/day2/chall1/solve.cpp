#include <fstream>
#include <iostream>
#include <sstream>

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

    ssize_t X = 0, Y = 0;
    std::string line;
    while (getline(inp, line)) {
        size_t idx = line.find(' ');
        std::string instr = line.substr(0, idx);
        size_t amt = std::stoi(line.substr(idx + 1));
        // std::cout << instr << " " << amt << std::endl;

        if (instr == "forward") {
            X += amt;
        } else if (instr == "down") {
            Y += amt;
        } else if (instr == "up") {
            Y -= amt;
        }
    }

    // std::cout << X << " " << Y << std::endl;

    std::cout << X * Y << std::endl;

    inp.close();
    return 0;
}
