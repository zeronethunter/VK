#include "ListGraph.h"

std::vector<int> ListGraph::GetNextVertices(int vertex) const noexcept {
  assert((vertex >= 0 && vertex < adjacency_list.size()));
  return adjacency_list[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const noexcept {
  assert((vertex >= 0 && vertex < adjacency_list.size()));
  std::vector<int> result;
  for (int i = 0; i < adjacency_list.size(); ++i) {
    for (auto child : adjacency_list[i]) {
      if (child == vertex) {
        result.push_back(i);
        break;
      }
    }
  }
  return result;
}

ListGraph::ListGraph(const IGraph& graph) {
  adjacency_list.resize(graph.VerticesCount());
  for (int i = 0; i < graph.VerticesCount(); ++i) {
    adjacency_list[i] = graph.GetNextVertices(i);
  }
}

ListGraph::ListGraph(int count) { adjacency_list.resize(count); }
void ListGraph::AddEdge(int from, int to) noexcept {
  assert((from < adjacency_list.size() && from >= 0));
  assert((to < adjacency_list.size() && to >= 0));

  adjacency_list[from].push_back(to);
}

size_t ListGraph::VerticesCount() const noexcept {
  return adjacency_list.size();
}
