#include "GraphIntreface.h"

#ifndef GRAPHINTERFACE_SETGRAPH_H
#define GRAPHINTERFACE_SETGRAPH_H

#include <iostream>
#include <unordered_set>
#include <vector>

class SetGraph : public IGraph {
 public:
  ~SetGraph() override = default;

  explicit SetGraph(const IGraph& graph) {
    adjacency_set.resize(graph.VerticesCount());
    for (int i = 0; i < adjacency_set.size(); ++i) {
      for (auto const& edge : graph.GetNextVertices(i)) {
        adjacency_set[i].insert(edge);
      }
    }
  }

  explicit SetGraph(int count = 0) noexcept { adjacency_set.resize(count); }

  void AddEdge(int from, int to) noexcept override {
    assert((from < adjacency_set.size() && from >= 0));
    assert((to < adjacency_set.size() && to >= 0));
    adjacency_set[from].insert(to);
  }

  [[nodiscard]] size_t VerticesCount() const noexcept override {
    return adjacency_set.size();
  }

  [[nodiscard]] std::vector<int> GetNextVertices(
      int vertex) const noexcept override {
    return {adjacency_set[vertex].begin(), adjacency_set[vertex].end()};
  }

  [[nodiscard]] std::vector<int> GetPrevVertices(
      int vertex) const noexcept override {
    std::vector<int> result;
    for (int i = 0; i < adjacency_set.size(); ++i) {
      if (adjacency_set[i].find(vertex) != adjacency_set[i].end()) {
        result.push_back(i);
      }
    }
    return result;
  }

 private:
  std::vector<std::unordered_set<int>> adjacency_set;
};

#endif  // GRAPHINTERFACE_SETGRAPH_H
