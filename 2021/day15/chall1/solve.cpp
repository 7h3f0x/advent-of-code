#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

class RiskGraph {
  private:
    std::vector<std::vector<int>> graph;
    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  public:
    void add_line(const std::string &line) {
        std::vector<int> row;

        for (auto ch : line) {
            if (ch >= '0' && ch <= '9')
                row.push_back(ch - '0');
            else {
                std::cerr << "Unable to parse character: " << ch
                          << " in line: " << line << std::endl;
                exit(1);
            }
        }

        graph.push_back(row);
    }

    size_t get_lowest_risk_path() {
        const size_t M = graph.size();
        const size_t N = graph[0].size();

        std::vector<std::vector<size_t>> dist(M,
                                              std::vector<size_t>(N, SIZE_MAX));
        using p = std::pair<size_t, std::pair<int, int>>;
        std::priority_queue<p, std::vector<p>, std::greater<p>> q;
        dist[0][0] = 0;
        q.push({0, {0, 0}});

        while (!q.empty()) {
            auto &top = q.top();

            int i = top.second.first;
            int j = top.second.second;

            if (i == M - 1 && j == N - 1)
                return top.first;

            if (dist[i][j] != top.first) {
                q.pop();
                continue;
            }

            for (auto &dir : directions) {
                int ii = i + dir.first;
                int jj = j + dir.second;
                if (ii >= 0 && ii < M && jj >= 0 && j < N &&
                    (dist[i][j] + graph[ii][jj] < dist[ii][jj])) {
                    dist[ii][jj] = dist[i][j] + graph[ii][jj];
                    q.push({dist[ii][jj], {ii, jj}});
                }
            }

            q.pop();
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

    RiskGraph graph;

    std::string line;
    while (getline(inp, line)) {
        graph.add_line(line);
    }

    std::cout << graph.get_lowest_risk_path() << std::endl;

    inp.close();
    return 0;
}
