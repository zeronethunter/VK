#include "GraphIntreface.h"

#ifndef GRAPHINTERFACE_MATRIXGRAPH_H
#define GRAPHINTERFACE_MATRIXGRAPH_H

#include <cassert>
#include <iostream>
#include <vector>

class MatrixGraph : public IGraph {
 public:
  ~MatrixGraph() override = default;

  explicit MatrixGraph(int count = 0);

  explicit MatrixGraph(const IGraph& graph);

  void AddEdge(int from, int to) noexcept override;

  [[nodiscard]] size_t VerticesCount() const noexcept override;

  [[nodiscard]] std::vector<int> GetNextVertices(
      int vertex) const noexcept override;

  [[nodiscard]] std::vector<int> GetPrevVertices(
      int vertex) const noexcept override;

 private:
  std::vector<std::vector<int>> adjacency_matrix;
};

#endif  // GRAPHINTERFACE_MATRIXGRAPH_H
