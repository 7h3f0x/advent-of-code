#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

class OctopusGrid {
  private:
    std::vector<std::vector<int>> octopuses;
    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    size_t num_flashes = 0;

    void simulate_step() {
        const size_t M = octopuses.size();
        const size_t N = octopuses[0].size();
        std::queue<std::pair<int, int>> flashing_q;
        std::vector<std::vector<bool>> done(M, std::vector<bool>(N, false));

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                octopuses[i][j] += 1;
                if (octopuses[i][j] > 9) {
                    done[i][j] = true;
                    flashing_q.push({i, j});
                }
            }
        }

        while (!flashing_q.empty()) {
            num_flashes += 1;
            auto &t = flashing_q.front();
            for (auto &dir : directions) {
                int i = t.first + dir.first;
                int j = t.second + dir.second;
                if (i >= 0 && i < M && j >= 0 && j < N && !done[i][j]) {
                    octopuses[i][j] += 1;
                    if (octopuses[i][j] > 9) {
                        done[i][j] = true;
                        flashing_q.push({i, j});
                    }
                }
            }
            flashing_q.pop();
        }

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (octopuses[i][j] > 9) {
                    octopuses[i][j] = 0;
                }
            }
        }
    }

  public:
    void add_from_line(const std::string &line) {
        std::vector<int> l;
        for (auto ch : line) {
            if (ch >= '0' && ch <= '9') {
                l.push_back(ch - '0');
            } else {
                std::cerr << "Unable to handle character: " << ch
                          << " in line : " << line << std::endl;
                exit(1);
            }
        }
        octopuses.push_back(l);
    }

    void simulate(int days) {
        for (int i = 0; i < days; ++i) {
            simulate_step();
        }
    }

    size_t get_flashes() const { return num_flashes; }
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

    OctopusGrid grid;
    std::string line;
    while (getline(inp, line)) {
        grid.add_from_line(line);
    }

    grid.simulate(100);

    std::cout << grid.get_flashes() << std::endl;

    inp.close();
    return 0;
}
