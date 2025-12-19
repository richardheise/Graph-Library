#include <stdio.h>
#include "graph.h"

//------------------------------------------------------------------------------

int main(void) {

  graph g = read_graph();
  
  printf("Number of vertices: %d\n", count_vertices(g) );

  printf("Number of edges: %d\n", count_edges(g) );

  printf("The maximum degree of graph g is: %d\n", max_degree(g));

  printf("The minimum degree of graph g is: %d\n", min_degree(g));

  printf("The average degree of graph g is: %d\n", avg_degree(g));

  printf("Regularity: %d\n", is_regular(g));

  printf("Completeness: %d\n", is_complete(g));

  printf("Triangles: %d\n", count_triangles(g));

  printf("Bipartite: %d\n", is_bipartite(g));
  
  printf("Original:");
  //write_graph(g);
  printf("\n");

  graph h = complement(g);

  printf("Complement:");
  //write_graph(h);
  printf("\n");

  printf("Connected: %d\n", is_connected(g));
  
  destroy_graph(g);
  destroy_graph(h);

  return 0;
}
