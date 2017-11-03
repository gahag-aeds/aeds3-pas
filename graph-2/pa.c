#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


// Subset in  Union-Find.
typedef struct Subset {
  size_t parent;
  size_t rank;
} Subset;
 
size_t disjoint_find(Subset* subsets, size_t i) {
  if (subsets[i].parent != i)
    subsets[i].parent = disjoint_find(subsets, subsets[i].parent);
  
  return subsets[i].parent;
}
 
void disjoint_union(Subset* subsets, size_t x, size_t y) {
  size_t xset = disjoint_find(subsets, x);
  size_t yset = disjoint_find(subsets, y);
  
  if (subsets[xset].rank < subsets[yset].rank)
    subsets[xset].parent = yset;
  else {
    if (subsets[xset].rank > subsets[yset].rank)
      subsets[yset].parent = xset;
    else {
      subsets[yset].parent = xset;
      subsets[xset].rank++;
    }
  }
}


typedef struct GraphEdge {
  size_t from, to;
  unsigned short weight;
} GraphEdge;

int compare_edges(const void* e1, const void* e2) {
  return ((GraphEdge*) e1)->weight > ((GraphEdge*) e2)->weight;
}


typedef struct SimpleGraph {
  size_t order;
  size_t size;
  
  GraphEdge edges[];
} SimpleGraph;
 
SimpleGraph* new_simplegraph(size_t order, size_t size) {
  SimpleGraph* g = calloc(1, sizeof(SimpleGraph) + sizeof(GraphEdge[size]));
  g->order = order;
  g->size = size;
  
  return g;
}

void delete_simplegraph(SimpleGraph** g) {
  assert(g != NULL);
  
  if (*g != NULL)
    free(*g);
  
  *g = NULL;
}

unsigned long simplegraph_mst(SimpleGraph* g) {
  size_t edges = 0; // count the edges already inserted in the mst
  size_t k = 0;     // iterator for the edges array
  
  unsigned long mst = 0;
  
  Subset* subsets = malloc(g->order * sizeof(Subset));
  
  for (size_t i = 0; i < g->order; i++) {
    subsets[i].parent = i;
    subsets[i].rank = 0;
  }
  
  qsort(g->edges, g->size, sizeof(GraphEdge), compare_edges);
  
  while (edges < g->order - 1) { // In the mst there are order - 1 edges.
    GraphEdge edge = g->edges[k];
    k++;
    
    size_t x = disjoint_find(subsets, edge.from);
    size_t y = disjoint_find(subsets, edge.to);
    
    if (x != y) { // If no cycles, add it to the mst.
      mst += edge.weight;
      edges++;
      
      disjoint_union(subsets, x, y);
    }
  }
  
  return mst;
}
 

int main() {
  unsigned short cities, roads;
  
  scanf("%hu %hu", &cities, &roads);
  do {
    SimpleGraph* g = new_simplegraph(cities, roads);
    
    for (unsigned short i = 0; i < roads; i++) {
      unsigned short from, to, distance;
      
      scanf("%hu %hu %hu", &from, &to, &distance);
      
      g->edges[i].from = from;
      g->edges[i].to = to;
      g->edges[i].weight = distance;
    }
    
    unsigned long sum = simplegraph_mst(g);
    
    delete_simplegraph(&g);
    
    printf("%lu\n", sum);
    
    scanf("%hu %hu", &cities, &roads);
  } while(cities != 0 && roads != 0);
  
  return 0;
}
