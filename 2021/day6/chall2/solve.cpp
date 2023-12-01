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
    static constexpr size_t CYCLE_TIME = 7;
    static constexpr size_t READY_TIME = 2;
    // group fishes having same reproduce time remaining into the same bucket.
    // For this question, just store the count of fishes in the bucket
    size_t fishes[CYCLE_TIME + READY_TIME];

  public:
    Simulator(const std::string &line) {
        for (auto &num : fishes) {
            num = 0;
        }
        for (auto num : split(line, ',')) {
            fishes[num] += 1;
        }
    }

    size_t num_fishes() const {
        size_t ans = 0;
        for (auto num : fishes) {
            ans += num;
        }
        return ans;
    }

    void simulate(size_t days) {
        /*
         * To decrement reproduce time remaining, just move fishes from bucket
         * `i + 1` to bucket `i`. For the bucket whose fishes reproduce, store
         * reproduced fishes(same number as the number reproducing) in last
         * bucket and add the original fishes to bucket at start of `CYCLE_TIME`
         */
        const size_t ARR_LEN = CYCLE_TIME + READY_TIME;
        for (; days > 0; days -= 1) {
            size_t reproducing_fishes = fishes[0];
            for (int i = 0; i < ARR_LEN - 1; ++i) {
                fishes[i] = fishes[i + 1];
            }
            fishes[CYCLE_TIME - 1] += reproducing_fishes;
            fishes[ARR_LEN - 1] = reproducing_fishes;
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
    sim.simulate(256);

    std::cout << sim.num_fishes() << std::endl;

    inp.close();
    return 0;
}
