#include <climits>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

class Polymer {
  private:
    struct ChainRule {
        // AB -> C
        char A, B, C;

        ChainRule(const std::string &line) {
            if (sscanf(line.c_str(), "%c%c -> %c", &A, &B, &C) != 3) {
                std::cerr << "Unable to parse rule: " << line << std::endl;
                exit(1);
            }
        }
    };

    std::list<char> chain;
    std::vector<ChainRule> rules;

    void do_step() {
        for (auto it = ++(chain.begin()); it != chain.end();) {
            auto next = it;
            ++next;
            auto prev = it;
            --prev;
            for (auto &rule : rules) {
                if (*prev == rule.A && *it == rule.B) {
                    chain.insert(it, rule.C);
                    break;
                }
            }
            it = next;
        }
    }

  public:
    Polymer() = default;
    Polymer(const std::string &line) {
        chain = std::list<char>(line.begin(), line.end());
    }

    void add_rule(const std::string &rule) { rules.push_back(ChainRule(rule)); }

    void perform_steps(int n) {
        for (int i = 0; i < n; ++i) {
            do_step();
        }
    }

    size_t answer() const {
        std::vector<size_t> counts(CHAR_MAX, 0);
        for (auto ch : chain) {
            counts[ch] += 1;
        }

        size_t min_val = SIZE_MAX, max_val = 0;
        for (auto count : counts) {
            if (count > max_val)
                max_val = count;

            if (count != 0 && count < min_val)
                min_val = count;
        }

        return max_val - min_val;
    }

    void show_chain() const {
        for (auto ch : chain) {
            std::cout << ch;
        }
        std::cout << std::endl;
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
    if (!getline(inp, line)) {
        std::cerr << "Unable to parse initial polymer seed: " << line
                  << std::endl;
        exit(1);
    }

    Polymer polymer(line);

    if (!getline(inp, line)) {
        std::cerr << "Unable to parse further" << std::endl;
        exit(1);
    }

    if (line != "") {
        std::cerr << "Expected empty line for separation: " << line
                  << std::endl;
        exit(1);
    }

    while (getline(inp, line)) {
        polymer.add_rule(line);
    }

    polymer.perform_steps(10);
    // polymer.show_chain();
    std::cout << polymer.answer() << std::endl;

    inp.close();
    return 0;
}
