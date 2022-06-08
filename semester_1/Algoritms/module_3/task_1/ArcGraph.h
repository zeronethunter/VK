#include "GraphIntreface.h"

#ifndef GRAPHINTERFACE_ARCGRAPH_H
#define GRAPHINTERFACE_ARCGRAPH_H

#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <vector>

class ArcGraph : public IGraph {
 public:
  ~ArcGraph() override = default;

  ArcGraph() noexcept = default;

  explicit ArcGraph(const IGraph& graph);

  void AddEdge(int from, int to) noexcept override;

  [[nodiscard]] size_t VerticesCount() const noexcept override;

  [[nodiscard]] std::vector<int> GetNextVertices(
      int vertex) const noexcept override;

  [[nodiscard]] std::vector<int> GetPrevVertices(
      int vertex) const noexcept override;

 private:
  std::vector<std::pair<int, int>> pair_vertices;
};

#endif  // GRAPHINTERFACE_ARCGRAPH_H
