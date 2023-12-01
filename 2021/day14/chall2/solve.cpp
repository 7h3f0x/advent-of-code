#include <fstream>
#include <iostream>
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

    std::vector<char> chain;
    std::vector<ChainRule> rules;

  public:
    Polymer() = default;
    Polymer(const std::string &line) {
        chain = std::vector<char>(line.begin(), line.end());
    }

    void add_rule(const std::string &rule) { rules.push_back(ChainRule(rule)); }

    size_t answer(size_t num_steps) const {
        // ~2D dp using rule.A,rule.B and steps remain
        std::vector<size_t[128]> dp[128][128];
        for (int i = 0; i < 128; ++i) {
            for (int j = 0; j < 128; ++j) {
                dp[i][j] = std::vector<size_t[128]>(num_steps + 1);
            }
        }

        for (auto &rule : rules) {
            auto &m = dp[rule.A][rule.B][0];
            m[rule.A] += 1;
            m[rule.B] += 1;
        }

        // AB -> C, i steps remain
        // dp[A][B][i] = sum(dp[A][C][i - 1], dp[C][B][i - 1])
        // dp[A][B][i][C] -= 1
        for (int i = 1; i <= num_steps; ++i) {
            for (auto &rule : rules) {
                auto &m = dp[rule.A][rule.B][i];
                auto &p1 = dp[rule.A][rule.C][i - 1];
                auto &p2 = dp[rule.C][rule.B][i - 1];

                for (int idx = 0; idx < 128; ++idx) {
                    m[idx] = p1[idx] + p2[idx];
                }

                // counted twice in `AC`, `CB`
                m[rule.C] -= 1;
            }
        }

        size_t counts[128] = {0};
        for (int i = 1; i < chain.size(); ++i) {
            char A = chain[i - 1];
            char B = chain[i];
            for (int j = 0; j < 128; ++j) {
                counts[j] += dp[A][B][num_steps][j];
            }
            if (i < chain.size() - 1)
                counts[B] -= 1;
        }

        // for (int i = 0; i < 128; ++i) {
        //     if (counts[i] != 0)
        //         std::cout << (char)i << " " << counts[i] << std::endl;
        // }

        size_t min = SIZE_MAX, max = 0;
        for (int i = 0; i < 128; ++i) {
            if (counts[i] > max)
                max = counts[i];
            else if (counts[i] != 0 && counts[i] < min)
                min = counts[i];
        }

        // std::cout << max << ":" << min << std::endl;
        return max - min;
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

    std::cout << polymer.answer(40) << std::endl;

    inp.close();
    return 0;
}
