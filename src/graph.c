// Richard Fernando Heise Ferreira GRR20191053

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

typedef Agedge_t *edge;

#define READ_ERROR -1
#define NODE_ERROR -2
#define GRAPH_ERROR -3
#define MALLOC_ERROR -4

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

graph read_graph(void) {

    graph g = agread(stdin, NULL);
    if ( !g ) {
        perror("Erro ao ler o graph, abortando.\n");
        exit(READ_ERROR);
    }

    return g; 
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void destroy_graph(graph g) {
    
    if ( !g ) {
        perror("graph nulo, abortando.\n");
        exit(GRAPH_ERROR);
    }

    agfree(g, NULL);

    return;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

graph write_graph(graph g) {
  
    if ( !g ) {
        perror("graph nulo, abortando.\n");
        exit(GRAPH_ERROR);
    }
    agwrite(g, stdout);

    return g;
    }

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int count_vertices(graph g) {
    
    if ( !g ) {
        perror("graph nulo, abortando.\n");
        exit(GRAPH_ERROR);
    }

    return agnnodes(g);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int count_edges(graph g) {
    
    if ( !g ) {
        perror("graph nulo, abortando.\n");
        exit(GRAPH_ERROR);
    }

    return agnedges(g);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int degree(vertex v, graph g) {
  
    if ( !v ) {
        perror("Vértice nulo, abortando.");
        exit(NODE_ERROR);
    }

    if ( !g ) {
        perror("graph nulo, abortando.\n");
        exit(GRAPH_ERROR);
    }

    
    return agdegree(g, v, TRUE, TRUE);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int max_degree(graph g)  {
  
    if ( !g ) {
        perror("graph nulo, abortando.\n");
        exit(GRAPH_ERROR);
    }

    vertex source;
    int max_deg = 0;
    int deg = 0;

    // Caminha nos nodos buscando o de maior degree
    for (source = agfstnode(g); source; source = agnxtnode(g, source)) {
        deg = agdegree(g, source, TRUE, TRUE);
        if ( max_deg < deg) {
            max_deg = deg;
        }
    }

    return max_deg;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int min_degree(graph g)  {
  
    if ( !g ) {
        perror("graph nulo, abortando.\n");
        exit(GRAPH_ERROR);
    }

    vertex source;
    int min_deg = 2147483647; // max int value
    int deg = 0;

    // Caminha nos nodos buscando o de menor degree
    for (source = agfstnode(g); source; source = agnxtnode(g, source)) {
        deg = agdegree(g, source, TRUE, TRUE);
        if ( min_deg > deg) {
            min_deg = deg;
        }
    }

    return min_deg;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int avg_degree(graph g) {
    
    if ( !g ) {
        perror("graph nulo, abortando.\n");
        exit(GRAPH_ERROR);
    }

    vertex source;
    int avg_deg = 0;
    int deg_sum = 0;

    for (source = agfstnode(g); source; source = agnxtnode(g, source)) {
        deg_sum += agdegree(g, source, TRUE, TRUE);
    }

    avg_deg = ( deg_sum / agnnodes(g) );

    return avg_deg;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int is_regular(graph g) {
  
    if ( !g ) {
        perror("graph nulo, abortando.\n");
        exit(GRAPH_ERROR);
    }

    vertex source = agfstnode(g);

    // enquanto há um próximo vértice
    while (agnxtnode(g, source)) {
        if (agdegree(g, source, TRUE, TRUE) != agdegree(g, agnxtnode(g, source), TRUE, TRUE) ) return 0;
        source = agnxtnode(g, source);
    }

    return 1;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int is_complete(graph g) {
  
    if ( !g ) {
        perror("graph nulo, abortando.\n");
        exit(GRAPH_ERROR);
    }

    int vertices = agnnodes(g);

    // número de vértices score 2 expandido e sem fatoriais
    int max_edges = ( (vertices * (vertices-1) ) / 2);

    return (agnedges(g) == max_edges); 
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Função local para buscar um vértice em um vetor de vértices de tamanho arbitrário
// custo linear
static int search_vector(vertex vector[], vertex elem, int size) {
    for (int i = 0; i < size; i++) {
        if (vector[i] == elem) {
            return 1;
        }
    }

    return 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int is_connected(graph g) {
  
    if ( !g ) {
        perror("graph nulo, abortando.\n");
        exit(GRAPH_ERROR);
    }

    int size = agnnodes(g);

    // pilha de vertices
    int i = 0;
    vertex stack[size];
    stack[i] = agfstnode(g);
    i++;

    // vetor de visitados
    int j = 0;
    vertex visited[size];
    
    // contador de vizinhos empilhados
    int c = 0;
    while (i) {

        // desempilha o top
        i--;
        vertex top = stack[i];

        // BFS
        // se não visitamos o top ainda
        if ( !search_vector(visited, top, i) ) {

        // buscamos os vizinhos do top
        for (vertex v1 = top; v1; v1 = agnxtnode(g, v1)) {
            if ( agedge(g, top, v1, NULL, FALSE)) {

                // se não visitamos os vizinhos, visitaremos ainda
                if ( !search_vector(visited, v1, j) ) {
                    stack[i] = v1; 
                    c++; // incremento do contador de vizinhos
                    i++;
                }
            }
        }

        // vizinho visitado
        visited[j] = top;
        j++;

        }
    }

    // se nosso contador de vizinhos foi todos os vizinhos, 
    // o graph é is_connected. Senão, não é.
    return (c == size-1);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int is_bipartite(graph g) {
  
    if ( !g ) {
        perror("graph nulo, abortando.\n");
        exit(GRAPH_ERROR);
    }

    // struct local com nodo e color do nodo
    typedef struct node_s {
        vertex n;
        short color;
    } node_t;

    int size = agnnodes(g);
    int i = 0;

    // vetor auxiliar de nodos
    node_t nodes[size];

    for (vertex source = agfstnode(g); source; source = agnxtnode(g, source)) {
        nodes[i].n = source;
        nodes[i].color = 0;
        i++;
    }

    // pilha de nodos
    i = 0;
    node_t stack[size];

    // para todo nodo, funciona para grafos disconectados e conectados
    for (int k = 0; k < size; k++) {

        // se o nodo em questão não foi colorido, colorimos e o empilhamos
        if (!nodes[k].color) {
            nodes[k].color = 1;
            stack[i] = nodes[k];
            i++;
        }

        // enquanto a pilha não estiver vazia
        while (i) {

        // desempilha o top
        i--;
        node_t top = stack[i];

        // busca por vizinhos do top
        for (int j = 0; j < size; j++) {
            if ( agedge(g, top.n, nodes[j].n, NULL, FALSE) ) {
            
                // se o vizinho não for colorido
                if (!nodes[j].color) {

                    // colorimos com uma color diferente ao do top
                    // só temos duas cores aqui
                    nodes[j].color = ((top.color % 2) + 1);

                    // empilhamos o vizinho
                    stack[i] = nodes[j]; 
                    i++;

                // se o vizinho tem a mesma color do top, o graph não é is_bipartite
                } else if (nodes[j].color == top.color) return 0;
            } 
        }
        }
    }
    
    // todos os vizinhos foram coloridos somente com duas cores
    // então o graph é is_bipartite
    return 1;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Função local para alocação dinâmica de matrizes de tamanho size
static int **alloc_matrix(int size) {
  
    int **matrix = malloc( size * sizeof(int *));

    if (!matrix) {
        perror("Erro ao alocar matrix de adjacência, abortando.\n");
        exit(MALLOC_ERROR);
    }

    for (int i = 0; i < size; i++) {
        matrix[i] = malloc(sizeof(int)*size);
        if (!matrix[i]) {
            perror("Erro ao alocar matrix de adjacência, abortando.\n");
            exit(MALLOC_ERROR);
        }
    }

    return matrix;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Função local para liberação de memória de matrizes m de tamanho size
static void free_matrix(int **m, int size) {
    for (int i = 0; i < size; i++)
        free(m[i]);
    free(m);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Função local que multiplica matrizes quadradas m1 e m2 de tamanho size
static int **multiply_matrix(int size, int **m1, int **m2) {

    int **mat = alloc_matrix(size);

    int sum = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mat[i][j] = 0;
            sum = 0;
            for (int k = 0; k < size; k++) {
                sum += m1[i][k] * m2[k][j];
            }
            mat[i][j] += sum;
        }
    }

  return mat;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Função local para printar matrix de adjacência
static void print_adjacency_matrix(int **m, int size) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// uma explicação detalhada do funcionamento dessa função pode ser encontrada aqui
// https://www.geeksforgeeks.org/number-of-triangles-in-a-undirected-graph/
int count_triangles(graph g) {
    
    if ( !g ) {
        perror("graph nulo, abortando.\n");
        exit(GRAPH_ERROR);
    }

    int size = agnnodes(g);

    int **adj_matrix = adjacency_matrix(g);
    int **aux_matrix = adjacency_matrix(g);

    // pegamos o cubo da matrix de adjacência em aux_matrix
    aux_matrix = multiply_matrix(size, adj_matrix, aux_matrix);
    aux_matrix = multiply_matrix(size, adj_matrix, aux_matrix);

    // pegamos o trace da matrix cúbica de adjacência
    int trace = 0;
    for (int i = 0; i < size; i++) {
        trace += aux_matrix[i][i];
    }

    // dividindo o trace por 2, pois o graph é não-direcionado
    // e depois por 3, pois são ciclos de tamanho 3
    int num_triangles = (trace / 6);

    free_matrix(adj_matrix, size);
    free_matrix(aux_matrix, size);

    return num_triangles;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int **adjacency_matrix(graph g) {
  
  if ( !g ) {
    perror("graph nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  int **adj = alloc_matrix(agnnodes(g));
  
  int i = 0;
  int j = 0;
  vertex source;
  vertex destination;

  // caminha por todos os vértices encontrando todas as arestas
  // e atribuindo 1s ou 0s na matrix de adjacência
  for (source = agfstnode(g); source; source = agnxtnode(g, source)) {
    j = 0;
    for(destination = agfstnode(g); destination; destination = agnxtnode(g, destination)) {
        adj[i][j] = ( (agedge(g, source, destination, NULL, FALSE)) ? 1 : 0 );
        j++;
    }
    i++;
  }

  return adj;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// função local para copiar um graph g, retorna o graph copiado
static graph copy_graph(graph g) {

  if ( !g ) {
    perror("graph nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  graph graph_copy = agopen("graph_copy", Agstrictundirected, NULL);
  vertex source;
  vertex destination;

  // copia vértices
  for (source = agfstnode(g); source; source = agnxtnode(g, source)) {
    agnode(graph_copy, agnameof(source), TRUE);
  }

  // copia arestas
  for (source = agfstnode(g); source; source = agnxtnode(g, source)) {
    for (destination = agnxtnode(g, source); destination; destination = agnxtnode(g, destination)) {
        if ( agedge(g, source, destination, NULL, FALSE) ) {
            agedge(graph_copy, agnode(graph_copy, agnameof(source), FALSE), agnode(graph_copy, agnameof(destination), FALSE), NULL, TRUE);
        }
    }
  }

  return graph_copy;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

graph complement(graph g) {
  
  if ( !g ) {
    perror("graph nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  graph g_comp = copy_graph(g);
  vertex source;
  vertex destination;
  

  // inverte as arestas do graph copiado: se o original tinha uma aresta entre dois nodos
  // o complementar não tem e vice-versa
  for (source = agfstnode(g_comp); source; source = agnxtnode(g_comp, source)) {
    for(destination = agnxtnode(g_comp, source); destination; destination = agnxtnode(g_comp, destination)) {
      if (source != destination) {

        edge e = agedge(g_comp, source, destination, NULL, FALSE);
        if (e == NULL) {
          agedge(g_comp, source, destination, NULL, TRUE);
        } else {
          agdeledge( g_comp, e );
        }
      }
    }
  }

  return g_comp;
}

