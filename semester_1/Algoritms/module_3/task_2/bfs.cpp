#include <iostream>
#include <vector>
#include <cassert>
#include <queue>

class IGraph {
public:
    virtual ~IGraph() noexcept = default;;

    virtual void AddEdge(int from, int to) noexcept = 0;

    [[nodiscard]] virtual size_t VerticesCount() const noexcept = 0;

    [[nodiscard]] virtual std::vector<int> GetAdjVertices(int vertex) const noexcept = 0;

    [[nodiscard]] size_t CountShortestDistBetween(int from, int to) const;
};

size_t IGraph::CountShortestDistBetween(int from, int to) const {
    if (from == to) {
        return 0;
    }

    std::queue<int> queue;

    std::vector<int> count_path_from_prev_level(VerticesCount(), 0);

    count_path_from_prev_level[from] = 1;

    queue.push(from);

    std::vector<int> level(VerticesCount(), INT8_MAX);

    level[from] = 0;

    // bfs based on levels, not on visited vertices
    while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();
        for (int child: GetAdjVertices(vertex)) {
            if (level[child] > level[vertex] + 1) {
                queue.push(child);
                level[child] = level[vertex] + 1;
                count_path_from_prev_level[child] = count_path_from_prev_level[vertex];
            } else if (level[child] == level[vertex] + 1) {
                count_path_from_prev_level[child] += count_path_from_prev_level[vertex];
            }
        }
    }

    return count_path_from_prev_level[to];
}

class VectorGraph : public IGraph {
public:

    explicit VectorGraph(size_t size = 0) : graph(size) {};

    ~VectorGraph() noexcept override = default;

    void AddEdge(int from, int to) noexcept override {
        assert((from >= 0 && from < graph.size()));
        assert((to >= 0 && to < graph.size()));
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    [[nodiscard]] size_t VerticesCount() const noexcept override {
        return graph.size();
    }

    [[nodiscard]] std::vector<int> GetAdjVertices(int vertex) const noexcept override {
        return {graph[vertex].cbegin(), graph[vertex].cend()};
    }

private:
    std::vector<std::vector<int>> graph;
};

void solve(size_t vertices, size_t edges) {
    IGraph *graph = new VectorGraph(vertices);
    int from, to;
    for (size_t i = 0; i < edges; ++i) {
        std::cin >> from >> to;
        graph->AddEdge(from, to);
    }

    std::cin >> from >> to;

    std::cout << graph->CountShortestDistBetween(from, to);

    delete graph;
}

int main() {
    size_t vertices;
    size_t edges;

    std::cin >> vertices >> edges;

    solve(vertices, edges);

    return 0;
}
