#include <climits>
#include <fstream>
#include <iostream>
#include <list>

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

    std::list<int> numbers;
    int idx = 0;
    size_t count = 0;
    std::string line;
    while (getline(inp, line)) {
        int val = std::stoi(line);
        if (idx >= 3) {
            // we are comparing `a + b + c` with `b + c + d`
            // thus we need to effectively compare only `a` and `d`
            if (val > numbers.front())
                count += 1;
            numbers.pop_front();
        }
        numbers.push_back(val);
        idx += 1;
    }

    std::cout << count << std::endl;

    inp.close();
    return 0;
}
