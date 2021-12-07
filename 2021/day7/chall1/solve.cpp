#include <algorithm>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Crabs {
  private:
    std::vector<int> positions;

    static std::vector<int> split(const std::string &line, const char ch) {
        std::vector<int> ret;

        std::stringstream ss(line);
        std::string num;
        while (getline(ss, num, ch))
            ret.push_back(std::stoi(num));

        return ret;
    }

  public:
    Crabs(const std::string &positions) {
        this->positions = split(positions, ',');
    }

    size_t get_fuel_cost() {
        size_t cost = SIZE_MAX;
        int min_val = INT_MAX;
        int max_val = INT_MIN;
        for (auto num : positions) {
            if (num > max_val) {
                max_val = num;
            } else if (num < min_val) {
                min_val = num;
            }
        }

        // TODO: find a better algo for this
        for (int i = min_val; i <= max_val; ++i) {
            size_t curr_cost = 0;
            for (auto num : positions) {
                curr_cost += std::abs(num - i);
            }
            cost = std::min(cost, curr_cost);
        }

        return cost;
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
    getline(inp, line);

    Crabs crabs(line);

    std::cout << crabs.get_fuel_cost() << std::endl;

    inp.close();
    return 0;
}
