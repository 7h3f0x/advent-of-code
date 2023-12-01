#include <fstream>
#include <iostream>
#include <string>
#include <vector>

typedef std::pair<int, int> Point;

class HeightMap {
  private:
    std::pair<int, int> directions[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    std::vector<std::string> heightmap;

  public:
    void add_line(const std::string &line) { heightmap.push_back(line); }

    std::vector<Point> get_low_points() {
        std::vector<Point> low_points;
        const size_t M = heightmap.size();
        const size_t N = heightmap[0].size();

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                bool is_valid = true;
                for (auto &dir : directions) {
                    int ii = i + dir.first;
                    int jj = j + dir.second;
                    if (ii >= 0 && ii < M && jj >= 0 && jj < N) {
                        if (heightmap[i][j] >= heightmap[ii][jj]) {
                            is_valid = false;
                            break;
                        }
                    }
                }
                if (is_valid) {
                    low_points.push_back({i, j});
                }
            }
        }

        return low_points;
    }

    int operator[](Point &p) const {
        return heightmap[p.first][p.second] - '0';
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

    HeightMap hmap;
    std::string line;
    while (getline(inp, line)) {
        hmap.add_line(line);
    }

    size_t risk_sum = 0;

    for (auto &point : hmap.get_low_points()) {
        risk_sum += hmap[point] + 1;
    }

    std::cout << risk_sum << std::endl;

    inp.close();
    return 0;
}
