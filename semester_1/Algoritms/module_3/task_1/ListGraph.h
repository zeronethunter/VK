#include "GraphIntreface.h"

#ifndef GRAPHINTERFACE_LISTGRAPH_H
#define GRAPHINTERFACE_LISTGRAPH_H

#include <cassert>
#include <iostream>
#include <vector>

class ListGraph : public IGraph {
 public:
  ~ListGraph() noexcept override = default;

  explicit ListGraph(const IGraph& graph);

  explicit ListGraph(int count = 0);

  void AddEdge(int from, int to) noexcept override;

  [[nodiscard]] size_t VerticesCount() const noexcept override;

  [[nodiscard]] std::vector<int> GetNextVertices(
      int vertex) const noexcept override;

  [[nodiscard]] std::vector<int> GetPrevVertices(
      int vertex) const noexcept override;

 private:
  std::vector<std::vector<int>> adjacency_list;
};

#endif  // GRAPHINTERFACE_LISTGRAPH_H
