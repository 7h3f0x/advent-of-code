#include <climits>
#include <fstream>
#include <iostream>
#include <vector>

class Plane {
  private:
    std::vector<std::vector<bool>> plane;
    size_t ht, wd;

  public:
    Plane(std::vector<std::pair<int, int>> &points) {
        int x_max, y_max;
        x_max = y_max = INT_MIN;
        for (auto &pt : points) {
            x_max = std::max(x_max, pt.first);
            y_max = std::max(y_max, pt.second);
        }

        x_max += 1;
        y_max += 1;

        ht = y_max;
        wd = x_max;

        using std::vector;
        plane = vector<vector<bool>>(x_max, vector<bool>(y_max, false));
        for (auto &pt : points) {
            plane[pt.first][pt.second] = true;
        }
    }

    void do_fold(std::pair<char, int> &fold) {
        if (fold.first == 'x') {
            for (int i = fold.second + 1; i < wd; ++i) {
                for (int j = 0; j < ht; ++j) {
                    int ii = fold.second - (i - fold.second);
                    plane[ii][j] = plane[ii][j] | plane[i][j];
                }
            }
            wd /= 2;
        } else if (fold.first == 'y') {
            for (int i = 0; i < wd; ++i) {
                for (int j = fold.second + 1; j < ht; ++j) {
                    int jj = fold.second - (j - fold.second);
                    plane[i][jj] = plane[i][jj] | plane[i][j];
                }
            }
            ht /= 2;
        }
    }

    size_t get_visible_dots() const {
        size_t count = 0;
        for (int i = 0; i < wd; ++i) {
            for (int j = 0; j < ht; ++j) {
                if (plane[i][j])
                    count += 1;
            }
        }

        return count;
    }

    void print_pattern() {
        for (int j = 0; j < ht; ++j) {
            for (int i = 0; i < wd; ++i) {
                if (plane[i][j])
                    std::cout << '#';
                else
                    std::cout << '.';
            }
            std::cout << std::endl;
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

    // parse out all the points
    std::vector<std::pair<int, int>> points;
    std::string line;
    while (getline(inp, line)) {
        if (line == "") {
            break;
        }
        int i, j;
        if (sscanf(line.c_str(), "%d,%d", &i, &j) != 2) {
            std::cerr << "Unable to parse line: " << line << std::endl;
            exit(1);
        }
        points.push_back({i, j});
    }

    Plane plane(points);

    // parse out all fold instructions
    std::vector<std::pair<char, int>> folds;
    while (getline(inp, line)) {
        char ch;
        int amt;
        if (sscanf(line.c_str(), "fold along %c=%d", &ch, &amt) != 2) {
            std::cerr << "Unable to parse line: " << line << std::endl;
            exit(1);
        }
        folds.push_back({ch, amt});
    }

    for (auto &fold : folds) {
        plane.do_fold(fold);
    }

    // `LGHEGUEJ` in sort of ascii art form
    plane.print_pattern();

    inp.close();
    return 0;
}
