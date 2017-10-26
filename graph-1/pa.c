#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Digraph {
  size_t vertices;
  
  bool edges[]; // Adjacency matrix.
} Digraph;

Digraph* new_digraph(size_t vertices) {
  assert(vertices > 1);
  
  Digraph* g = calloc(1, sizeof(Digraph) + sizeof(bool[vertices][vertices]));
  
  if (g == NULL)
    return NULL;
  
  g->vertices = vertices;
  
  return g;
}

void delete_digraph(Digraph** g) {
  assert(g != NULL);
  
  if (*g != NULL)
    free(*g);
  
  *g = NULL;
}

size_t digraph_vertices(Digraph* g) {
  assert(g != NULL);
  
  return g->vertices;
}

bool* digraph_edge(Digraph* g, size_t i, size_t j) {
  assert(g != NULL);
  
  bool (*edges)[g->vertices][g->vertices] = (void*) g->edges;
  
  return &(*edges)[i][j];
}


Digraph* digraph_transposed(Digraph* g) {
  assert(g != NULL);
  
  size_t vertices = digraph_vertices(g);
  Digraph* t = new_digraph(vertices);
  
  if (t == NULL)
    return NULL;
  
  for (size_t i = 0; i < vertices; i++)
    for (size_t j = 0; j < vertices; j++)
      *digraph_edge(t, j, i) = *digraph_edge(g, i, j);
  
  return t;
}

void digraph_dfs(Digraph* g, size_t v, bool* visited) {
  assert(g != NULL);
  
  visited[v] = true;
  
  for (size_t j = 0; j < digraph_vertices(g); j++)
    if (*digraph_edge(g, v, j))
      if (!visited[j])
        digraph_dfs(g, j, visited);
}

bool digraph_strongly_conected(Digraph* g) {
  assert(g != NULL);
  
  size_t vertices = digraph_vertices(g);
  bool* visited = calloc(vertices, sizeof(bool));
  
  
  digraph_dfs(g, 0, visited);
  
  for (size_t i = 0; i < vertices; i++)
    if (!visited[i]) {
      free(visited);
      
      return false;
    }
  
  
  Digraph* t = digraph_transposed(g);
  
  memset(visited, false, vertices * sizeof(bool));
  
  digraph_dfs(t, 0, visited);
  
  delete_digraph(&t);
  
  for (size_t i = 0; i < vertices; i++)
    if (!visited[i]) {
      free(visited);
      
      return false;
    }
  
  free(visited);
  
  return true;
}



int main() {
  unsigned long isections, streets;
  
  scanf("%lu %lu", &isections, &streets);
  do {
    Digraph* g = new_digraph(isections);
    
    for (unsigned long i = 0; i < streets; i++) {
      unsigned long from, to;
      unsigned char direction;
      
      scanf("%lu %lu %hhu", &from, &to, &direction);
      
      from--;
      to--;
      
      *digraph_edge(g, from, to) = true;
      
      if (direction == 2)
        *digraph_edge(g, to, from) = true;
    }
    
    bool strongly_conected = digraph_strongly_conected(g);
    
    delete_digraph(&g);
    
    printf("%d\n", (int) strongly_conected);
    
    scanf("%lu %lu", &isections, &streets);
  } while(isections != 0 && streets != 0);
  
  return 0;
}
