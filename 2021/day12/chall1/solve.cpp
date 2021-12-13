#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

class Graph {
  private:
    std::map<std::string, std::vector<std::string>> adj;

    static bool is_uppercase(const std::string &str) {
        for (auto ch : str) {
            if (!std::isupper(ch))
                return false;
        }

        return true;
    }

    size_t dfs_helper(const std::string &start,
                      std::map<std::string, bool> &visited) {
        if (start == "end") {
            return 1;
        }

        size_t ans = 0;
        for (auto &neigh : adj[start]) {
            if (!visited[neigh] || is_uppercase(neigh)) {
                visited[neigh] = true;
                ans += dfs_helper(neigh, visited);
                visited[neigh] = false;
            }
        }
        return ans;
    }

  public:
    void add_edge(const std::string &line) {
        int idx = line.find("-");
        if (idx == std::string::npos) {
            std::cerr << "Unable to parse line: " << line << std::endl;
            exit(1);
        }

        std::string p1 = line.substr(0, idx);
        std::string p2 = line.substr(idx + 1);

        if (adj.find(p1) == adj.end())
            adj[p1] = {p2};
        else
            adj[p1].push_back(p2);

        if (adj.find(p2) == adj.end())
            adj[p2] = {p1};
        else
            adj[p2].push_back(p1);
    }

    size_t get_distinct_paths() {
        std::map<std::string, bool> visited;
        for (auto &p : adj) {
            visited[p.first] = false;
        }

        visited["start"] = true;
        return dfs_helper("start", visited);
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

    Graph graph;

    std::string line;
    while (getline(inp, line)) {
        graph.add_edge(line);
    }

    std::cout << graph.get_distinct_paths() << std::endl;

    inp.close();
    return 0;
}
