# Biblioteca de Grafos

Este repositório contém uma biblioteca para manipulação de grafos, implementada em C. A biblioteca utiliza a `cgraph` (parte do projeto Graphviz) para a representação de grafos.

## Autor

Richard Fernando Heise Ferreira GRR20191053

## Estrutura do Repositório

O repositório está organizado da seguinte forma:

-   `include/`: Contém os arquivos de cabeçalho (`.h`).
    -   `graph.h`: Define a interface da biblioteca de grafos.
-   `src/`: Contém os arquivos de código-fonte (`.c`).
    -   `graph.c`: Implementação das funções da biblioteca de grafos.
    -   `test.c`: Programa de teste para a biblioteca.
-   `examples/`: Contém exemplos de grafos no formato DOT.
-   `makefile`: Arquivo para compilação do projeto.
-   `README.md`: Este arquivo.

## Funcionalidades

A biblioteca oferece as seguintes funcionalidades:

-   **Leitura e Escrita:**
    -   `read_graph()`: Lê um grafo da entrada padrão no formato DOT.
    -   `write_graph()`: Escreve um grafo na saída padrão no formato DOT.
    -   `destroy_graph()`: Libera a memória alocada para um grafo.

-   **Propriedades do Grafo:**
    -   `count_vertices()`: Retorna o número de vértices do grafo.
    -   `count_edges()`: Retorna o número de arestas do grafo.
    -   `degree()`: Retorna o grau de um vértice específico.
    -   `max_degree()`: Retorna o grau máximo do grafo.
    -   `min_degree()`: Retorna o grau mínimo do grafo.
    -   `avg_degree()`: Retorna o grau médio do grafo.

-   **Verificações do Grafo:**
    -   `is_regular()`: Verifica se o grafo é regular.
    -   `is_complete()`: Verifica se o grafo é completo.
    -   `is_connected()`: Verifica se o grafo é conexo (implementado com busca em largura - BFS).
    -   `is_bipartite()`: Verifica se o grafo é bipartido (implementado com coloração de vértices).

-   **Outras Operações:**
    -   `count_triangles()`: Retorna o número de triângulos no grafo (subgrafos completos de 3 vértices), utilizando o cubo da matriz de adjacência.
    -   `adjacency_matrix()`: Retorna a matriz de adjacência do grafo.
    -   `complement()`: Retorna o grafo complementar.

## Compilação e Execução

Para compilar o projeto, utilize o comando `make`:

```bash
make
```

Isso irá gerar o executável `test` no diretório raiz.

Para executar o programa de teste com um dos exemplos:

```bash
./test < examples/cidades.dot
```

Para limpar os arquivos gerados pela compilação:

```bash
make clean
```

## Observações

O código foi compilado com as flags de warning ativadas no `makefile`. Alguns warnings podem ser exibidos, a maioria deles relacionados à biblioteca `cgraph`.
