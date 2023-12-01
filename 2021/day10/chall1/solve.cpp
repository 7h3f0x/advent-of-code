#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

class Checker {
  private:
    std::unordered_map<char, std::pair<char, unsigned long long>> delimiters = {
        {')', {'(', 3}},
        {']', {'[', 57}},
        {'}', {'{', 1197}},
        {'>', {'<', 25137}}};

  public:
    unsigned long long get_syntax_error_score(const std::string &line) {
        std::stack<char> st;
        for (auto ch : line) {
            if (delimiters.find(ch) == delimiters.end())
                st.push(ch);
            else {
                auto &p = delimiters[ch];
                if (st.top() != p.first) {
                    return p.second;
                }
                st.pop();
            }
        }
        return 0;
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
    unsigned long long score = 0;
    std::string line;
    while (getline(inp, line)) {
        score += checker.get_syntax_error_score(line);
    }

    std::cout << score << std::endl;

    inp.close();
    return 0;
}
