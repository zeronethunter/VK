#ifndef GRAPHINTERFACE_GRAPHINTREFACE_H
#define GRAPHINTERFACE_GRAPHINTREFACE_H

#include <iostream>
#include <vector>

struct IGraph {
  virtual ~IGraph() noexcept = default;
  ;

  virtual void AddEdge(int from, int to) noexcept = 0;

  [[nodiscard]] virtual size_t VerticesCount() const noexcept = 0;

  [[nodiscard]] virtual std::vector<int> GetNextVertices(
      int vertex) const noexcept = 0;
  [[nodiscard]] virtual std::vector<int> GetPrevVertices(
      int vertex) const noexcept = 0;

  friend std::ostream& operator<<(std::ostream& out, const IGraph& graph) {
    out << "<==============================================================>\n";
    for (int i = 0; i < graph.VerticesCount(); ++i) {
      size_t beautify = 0;
      for (int vertex : graph.GetNextVertices(i)) {
        if (beautify + 1 != graph.GetNextVertices(i).size()) {
          out << i << " -> " << vertex << ", ";
        } else {
          out << i << " -> " << vertex;
        }
        ++beautify;
      }
      out << "\n";
    }
    out << "<==============================================================>";
    return out;
  };
};

#endif  // GRAPHINTERFACE_GRAPHINTREFACE_H
