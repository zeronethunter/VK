#include "MatrixGraph.h"

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const noexcept {
  std::vector<int> result;
  for (int i = 0; i < adjacency_matrix.size(); ++i) {
    if (adjacency_matrix[vertex][i]) {
      result.push_back(i);
    }
  }
  return result;
}
std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const noexcept {
  std::vector<int> result;
  for (int i = 0; i < adjacency_matrix.size(); ++i) {
    if (adjacency_matrix[i][vertex]) {
      result.push_back(i);
    }
  }
  return result;
}
MatrixGraph::MatrixGraph(int count) {
  adjacency_matrix.resize(count);
  for (size_t j = 0; j < count; ++j) {
    adjacency_matrix[j].resize(count);
  }
}
MatrixGraph::MatrixGraph(const IGraph& graph) {
  size_t count = graph.VerticesCount();
  adjacency_matrix.resize(count);
  for (int i = 0; i < count; ++i) {
    adjacency_matrix[i].resize(count, 0);
    for (size_t j : graph.GetNextVertices(i)) {
      adjacency_matrix[i][j] = 1;
    }
  }
}
void MatrixGraph::AddEdge(int from, int to) noexcept {
  assert((from < adjacency_matrix.size() && from >= 0));
  assert((to < adjacency_matrix.size() && to >= 0));

  adjacency_matrix[from][to] = 1;
}
size_t MatrixGraph::VerticesCount() const noexcept {
  return adjacency_matrix.size();
}
