#ifndef _GRAFO_H
#define _GRAFO_H

#include <graphviz/cgraph.h>

//------------------------------------------------------------------------------

typedef Agraph_t *graph;
typedef Agnode_t *vertex;

// -----------------------------------------------------------------------------
// devolve o grafo lido da entrada padrão (formato dot)

graph read_graph(void);

// -----------------------------------------------------------------------------
// desaloca g

void destroy_graph(graph g);

// -----------------------------------------------------------------------------
// escreve g na saída padrão em formato dot
// devolve g

graph write_graph(graph g);

// -----------------------------------------------------------------------------
// devolve o número de vértices de g

int count_vertices(graph g);


// -----------------------------------------------------------------------------
// devolve o número de arestas do grafo

int count_edges(graph g);


// -----------------------------------------------------------------------------
// devolve o grau do vértice v em g

int degree(vertex v, graph g);

// -----------------------------------------------------------------------------
// devolve o grau máximo de g

int max_degree(graph g);

// -----------------------------------------------------------------------------
// devolve o grau mínimo de g

int min_degree(graph g);

// -----------------------------------------------------------------------------
// devolve o grau médio de g

int avg_degree(graph g);

//------------------------------------------------------------------------------
// devolve 1 se g é regular, ou 0 caso contrário

int is_regular(graph g);

//------------------------------------------------------------------------------
// devolve 1 se g é completo, ou 0 caso contrário

int is_complete(graph g);

//------------------------------------------------------------------------------
// devolve 1 se g é conexo, ou 0 caso contrário

int is_connected(graph g);

//------------------------------------------------------------------------------
// devolve 1 se g é bipartido, ou 0 caso contrário

int is_bipartite(graph g);

//------------------------------------------------------------------------------
// devolve o número de triângulos (subgrafos completos de 3 vértices) em g

int count_triangles(graph g);

//------------------------------------------------------------------------------
// devolve uma matriz de adjacência de g onde as linhas/colunas
// estão ordenadas do mesmo modo que agfstnode() e agnxtnode()
// em libcgraph

int **adjacency_matrix(graph g);

//------------------------------------------------------------------------------
// devolve o grafo complementar a g

graph complement(graph g);

#endif
