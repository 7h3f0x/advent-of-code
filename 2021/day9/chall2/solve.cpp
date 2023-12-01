#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

typedef std::pair<int, int> Point;
typedef std::vector<Point> Basin;

class HeightMap {
  private:
    std::pair<int, int> directions[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    std::vector<std::string> heightmap;

    Basin get_basin(Point &start, std::vector<std::vector<bool>> &visited) {
        const size_t M = visited.size();
        const size_t N = visited[0].size();
        Basin basin;
        std::queue<Point> q;
        q.push(start);
        visited[start.first][start.second] = true;
        basin.push_back({start.first, start.second});

        while (!q.empty()) {
            auto &pt = q.front();
            int i = pt.first, j = pt.second;
            for (auto &dir : directions) {
                int ii = i + dir.first;
                int jj = j + dir.second;
                if (ii >= 0 && ii < M && jj >= 0 && jj < N) {
                    if ((!visited[ii][jj]) && (heightmap[ii][jj] != '9') &&
                        heightmap[ii][jj] >= heightmap[i][j]) {
                        q.push({ii, jj});
                        basin.push_back({ii, jj});
                        visited[ii][jj] = true;
                    }
                }
            }

            q.pop();
        }

        return basin;
    }

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

    std::vector<Basin> get_basins() {
        const size_t M = heightmap.size();
        const size_t N = heightmap[0].size();
        std::vector<Basin> ret;
        std::vector<std::vector<bool>> visited(M, std::vector<bool>(N, false));

        for (auto &low_pt : get_low_points()) {
            ret.push_back(get_basin(low_pt, visited));
        }

        return ret;
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

    std::vector<int> basin_sizes;
    for (auto &basin : hmap.get_basins()) {
        basin_sizes.push_back(basin.size());
    }

    std::sort(basin_sizes.begin(), basin_sizes.end());
    size_t ans = 1;
    int i = 0;
    for (auto it = basin_sizes.rbegin(); it != basin_sizes.rend(); ++it) {
        if (i == 3) {
            break;
        }
        ans *= *it;
        i += 1;
    }

    std::cout << ans << std::endl;

    inp.close();
    return 0;
}
