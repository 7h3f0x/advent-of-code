#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

std::vector<int> split(const std::string &s, char ch) {
    std::vector<int> items;
    std::stringstream ss(s);
    std::string tmp;
    while (getline(ss, tmp, ch))
        items.push_back(std::stoi(tmp));
    return items;
}

class Simulator {
  private:
    std::vector<int> fishes;

  public:
    static constexpr size_t CYCLE_TIME = 7;
    static constexpr size_t READY_TIME = 2;

    Simulator(const std::string &line) { fishes = split(line, ','); }

    size_t num_fishes() const { return fishes.size(); }

    void simulate(size_t days) {
        std::vector<int> tmp;
        for (; days > 0; days -= 1) {
            for (auto &fish : fishes) {
                if (fish == 0) {
                    tmp.push_back(CYCLE_TIME + READY_TIME - 1);
                    fish = CYCLE_TIME - 1;
                } else {
                    fish -= 1;
                }
            }
            fishes.insert(fishes.end(), tmp.begin(), tmp.end());
            tmp.clear();
        }
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

    Simulator sim(line);
    sim.simulate(80);

    std::cout << sim.num_fishes() << std::endl;

    inp.close();
    return 0;
}
