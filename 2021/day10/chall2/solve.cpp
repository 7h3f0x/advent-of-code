#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

class Checker {
  private:
    std::unordered_map<char, std::pair<char, unsigned long long>> delimiters = {
        {'(', {')', 1}}, {'[', {']', 2}}, {'{', {'}', 3}}, {'<', {'>', 4}}};

  public:
    unsigned long long get_autocomplete_score(const std::string &line) {
        std::stack<char> st;
        for (auto ch : line) {
            if (delimiters.find(ch) != delimiters.end())
                st.push(ch);
            else {
                if (ch != delimiters[st.top()].first) {
                    return 0;
                }
                st.pop();
            }
        }
        unsigned long long score = 0;
        while (!st.empty()) {
            score *= 5;
            score += delimiters[st.top()].second;
            st.pop();
        }
        return score;
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

    Checker checker;
    std::vector<unsigned long long> autocomplete_scores;
    std::string line;
    while (getline(inp, line)) {
        unsigned long long score = checker.get_autocomplete_score(line);
        if (score)
            autocomplete_scores.push_back(score);
    }

    std::sort(autocomplete_scores.begin(), autocomplete_scores.end());

    const size_t N = autocomplete_scores.size();

    std::cout << autocomplete_scores[N / 2] << std::endl;

    inp.close();
    return 0;
}
