#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <list>
#include <set>

class IGraph {
public:
    virtual ~IGraph() noexcept = default;;

    virtual void AddEdge(int from, int to, int weight) noexcept = 0;

    [[nodiscard]] virtual size_t VerticesCount() const noexcept = 0;

    [[nodiscard]] virtual std::vector<std::pair<int, int>> GetAdjVertices(int vertex) const noexcept = 0;

    [[nodiscard]] int ShortestDist(int from, int to) const noexcept;

};

int IGraph::ShortestDist(int from, int to) const noexcept {
    // Dijkstra algorithm

    size_t n = VerticesCount();

    std::vector<int> distances(n, INT32_MAX);

    distances[from] = 0;

    std::set<std::pair<int, int>> priority_queue;

    priority_queue.insert({from, 0});

    while (!priority_queue.empty()) {
        std::pair<int, int> u = *priority_queue.begin();
        priority_queue.erase(priority_queue.begin());
        for (const auto &v: GetAdjVertices(u.first)) {
            if (distances[v.first] > distances[u.first] + v.second) {
                if (distances[v.first] != INT32_MAX) {
                    priority_queue.erase({v.first, distances[v.first]});
                }

                distances[v.first] = distances[u.first] + v.second;
                priority_queue.insert({v.first, distances[v.first]});
            }
        }
    }
    if (distances[to] == INT32_MAX) {
        return -1;
    }
    return distances[to];
}

class MatrixGraph : public IGraph {
public:

    explicit MatrixGraph(size_t size = 0) : graph(size) {};

    ~MatrixGraph() noexcept override = default;

    void AddEdge(int from, int to, int weight) noexcept override {
        assert((from >= 0 && from < graph.size()));
        assert((to >= 0 && to < graph.size()));
        graph[from].push_back({to, weight});
        graph[to].push_back({from, weight});
    }

    [[nodiscard]] size_t VerticesCount() const noexcept override {
        return graph.size();
    }

    [[nodiscard]] std::vector<std::pair<int, int>> GetAdjVertices(int vertex) const noexcept override {
        assert((vertex >= 0 && vertex < graph.size()));
        return {graph[vertex].begin(), graph[vertex].end()};
    }

private:
    std::vector<std::list<std::pair<int, int>>> graph;
};

void solve(size_t n, size_t m) {
    IGraph *graph = new MatrixGraph(n);
    int from, to;
    for (size_t i = 0; i < m; ++i) {
        int weight;
        std::cin >> from >> to >> weight;
        graph->AddEdge(from, to, weight);
    }

    std::cin >> from >> to;

    std::cout << graph->ShortestDist(from, to);

    delete graph;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;

    solve(n, m);

    return 0;
}
