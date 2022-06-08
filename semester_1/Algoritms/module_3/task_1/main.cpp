#include "ArcGraph.h"
#include "GraphIntreface.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"

int main() {
  std::cout
      << "<============================TEST01============================>";
  std::cout << std::endl;

  ListGraph list_graph(6);

  list_graph.AddEdge(0, 1);
  list_graph.AddEdge(0, 2);
  list_graph.AddEdge(0, 3);
  list_graph.AddEdge(1, 2);
  list_graph.AddEdge(2, 3);

  list_graph.AddEdge(3, 1);
  list_graph.AddEdge(5, 1);
  list_graph.AddEdge(2, 5);
  list_graph.AddEdge(4, 2);
  list_graph.AddEdge(2, 4);

  std::cout << list_graph << "\n\n";

  MatrixGraph matrix_graph(list_graph);
  std::cout << matrix_graph << "\n\n";

  SetGraph set_graph(list_graph);
  std::cout << set_graph << "\n\n";

  ArcGraph arc_graph(list_graph);
  std::cout << arc_graph << "\n\n";

  std::cout
      << "<============================TEST02============================>";
  std::cout << std::endl;

  MatrixGraph matrix_graph_2(6);

  matrix_graph_2.AddEdge(0, 1);
  matrix_graph_2.AddEdge(0, 2);
  matrix_graph_2.AddEdge(0, 3);
  matrix_graph_2.AddEdge(1, 2);
  matrix_graph_2.AddEdge(2, 3);

  matrix_graph_2.AddEdge(3, 1);
  matrix_graph_2.AddEdge(5, 1);
  matrix_graph_2.AddEdge(2, 5);
  matrix_graph_2.AddEdge(4, 2);
  matrix_graph_2.AddEdge(2, 4);

  std::cout << matrix_graph_2 << "\n\n";

  ListGraph list_graph_2(list_graph);
  std::cout << list_graph_2 << "\n\n";

  SetGraph set_graph_2(list_graph);
  std::cout << set_graph_2 << "\n\n";

  ArcGraph arc_graph_2(list_graph);
  std::cout << arc_graph_2 << "\n\n";

  std::cout
      << "<============================TEST03============================>";
  std::cout << std::endl;

  SetGraph set_graph_3(6);

  set_graph_3.AddEdge(0, 1);
  set_graph_3.AddEdge(0, 2);
  set_graph_3.AddEdge(0, 3);
  set_graph_3.AddEdge(1, 2);
  set_graph_3.AddEdge(2, 3);

  set_graph_3.AddEdge(3, 1);
  set_graph_3.AddEdge(5, 1);
  set_graph_3.AddEdge(2, 5);
  set_graph_3.AddEdge(4, 2);
  set_graph_3.AddEdge(2, 4);

  std::cout << set_graph_3 << "\n\n";

  ListGraph list_graph_3(list_graph);
  std::cout << list_graph_3 << "\n\n";

  MatrixGraph matrix_graph_3(list_graph);
  std::cout << matrix_graph_3 << "\n\n";

  ArcGraph arc_graph_3(list_graph);
  std::cout << arc_graph_3 << "\n\n";

  std::cout
      << "<============================TEST04============================>";
  std::cout << std::endl;

  ArcGraph arc_graph_4;

  arc_graph_4.AddEdge(0, 1);
  arc_graph_4.AddEdge(0, 2);
  arc_graph_4.AddEdge(0, 3);
  arc_graph_4.AddEdge(1, 2);
  arc_graph_4.AddEdge(2, 3);

  arc_graph_4.AddEdge(3, 1);
  arc_graph_4.AddEdge(5, 1);
  arc_graph_4.AddEdge(2, 5);
  arc_graph_4.AddEdge(4, 2);
  arc_graph_4.AddEdge(2, 4);

  std::cout << arc_graph_4 << "\n\n";

  ListGraph list_graph_4(arc_graph_4);
  std::cout << list_graph_4 << "\n\n";

  MatrixGraph matrix_graph_4(arc_graph_4);
  std::cout << matrix_graph_4 << "\n\n";

  SetGraph set_graph_4(arc_graph_4);
  std::cout << set_graph_4 << "\n\n";

  return 0;
}
