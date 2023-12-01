#include <fstream>
#include <iostream>
#include <map>

class Field {
  private:
    std::map<std::pair<int, int>, size_t> field;
    void add_point(int x, int y) {
        // std::cout << x << "," << y << std::endl;
        if (field.find({x, y}) == field.end())
            field[{x, y}] = 0;
        field[{x, y}] += 1;
    }

  public:
    void add_line(const std::string &line) {
        int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
        if (sscanf(line.c_str(), "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) != 4) {
            std::cerr << "Unable to parse line: " << line << std::endl;
            exit(1);
        }

        if (x1 == x2) {
            // horizonal line
            if (y1 > y2)
                std::swap(y1, y2);

            for (; y1 <= y2; ++y1) {
                add_point(x1, y1);
            }
        } else if (y1 == y2) {
            // vertical line
            if (x1 > x2)
                std::swap(x1, x2);

            for (; x1 <= x2; ++x1) {
                add_point(x1, y1);
            }
        } else {
            // Only handle horizonal and vertical lines for now
        }
    }

    size_t get_count() {
        size_t count = 0;
        for (auto p : field) {
            size_t val = p.second;
            if (val >= 2) {
                // std::cout << p.first.first << " " << p.first.second
                //           << std::endl;
                count += 1;
            }
        }
        return count;
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

    Field field;
    std::string line;
    while (getline(inp, line)) {
        field.add_line(line);
    }

    std::cout << field.get_count() << std::endl;

    inp.close();
    return 0;
}
