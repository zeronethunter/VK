#include "ArcGraph.h"

void ArcGraph::AddEdge(int from, int to) noexcept {
  assert(from >= 0);
  assert(to >= 0);
  bool is_found = false;
  for (auto const& pair : pair_vertices) {
    if (pair.first == from && pair.second == from) {
      is_found = true;
    }
  }

  if (!is_found) {
    pair_vertices.emplace_back(from, to);
  }
}

size_t ArcGraph::VerticesCount() const noexcept {
  std::set<int> vertices;
  for (auto const& pair : pair_vertices) {
    vertices.insert(pair.first);
    vertices.insert(pair.second);
  }
  return vertices.size();
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const noexcept {
  std::vector<int> result;
  for (const auto& pair : pair_vertices) {
    if (pair.first == vertex) {
      result.push_back(pair.second);
    }
  }
  return result;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const noexcept {
  std::vector<int> result;
  for (const auto& pair : pair_vertices) {
    if (pair.second == vertex) {
      result.push_back(pair.first);
    }
  }
  return result;
}

ArcGraph::ArcGraph(const IGraph& graph) {
  for (int i = 0; i < graph.VerticesCount(); ++i) {
    auto it_edges = graph.GetNextVertices(i);
    for (const auto& child : it_edges) {
      pair_vertices.emplace_back(i, child);
    }
  }
}
