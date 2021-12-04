#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

std::vector<int> split(const std::string &s, char ch) {
    std::vector<int> ret;

    std::stringstream ss(s);
    std::string num;
    while (getline(ss, num, ch)) {
        if (num != "")
            ret.push_back(std::stoi(num));
    }

    return ret;
}

class Board {
  public:
    static constexpr size_t BOARD_SIZE = 5;

  private:
    bool found[BOARD_SIZE][BOARD_SIZE] = {0};
    std::unordered_map<int, std::pair<int, int>> map;
    int row = 0;

  public:
    Board() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                found[i][j] = false;
            }
        }
    }

    void add_line(const std::string &line) {
        std::vector<int> nums = split(line, ' ');
        for (int j = 0; j < nums.size(); ++j) {
            map[nums[j]] = {row, j};
        }
        row += 1;
    }

    // returns the place in which the number was found, else nullptr
    std::pair<int, int> *play(int num) {
        if (map.find(num) != map.end()) {
            auto &p = map[num];
            found[p.first][p.second] = true;
            return &p;
        }
        return nullptr;
    }

    bool check(int row, int col) {
        // check the row and col to find if we have won
        bool ret = true;
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (!found[row][j]) {
                ret = false;
                break;
            }
        }

        if (!ret) {
            ret = true;
            for (int i = 0; i < BOARD_SIZE; ++i) {
                if (!found[i][col]) {
                    ret = false;
                    break;
                }
            }
        }
        return ret;
    }

    size_t result(int num) {
        size_t res = 0;
        for (auto &p : map) {
            if (!found[p.second.first][p.second.second]) {
                res += p.first;
            }
        }
        return res * num;
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
    std::vector<int> numbers;
    std::vector<Board> boards;

    int idx = 0;
    while (getline(inp, line)) {
        if (idx == 0) {
            numbers = split(line, ',');
        } else {
            if (line == "") {
                boards.push_back(Board());
            } else {
                boards.back().add_line(line);
            }
        }
        idx += 1;
    }

    for (auto num : numbers) {
        for (auto &board : boards) {
            auto p = board.play(num);
            if (!p) {
                continue;
            }
            if (board.check(p->first, p->second)) {
                std::cout << board.result(num) << std::endl;
                goto END;
            }
        }
    }

END:
    inp.close();
    return 0;
}
