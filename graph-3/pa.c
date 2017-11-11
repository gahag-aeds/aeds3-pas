#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned short order;
short graph[1000][1000];

struct {
  unsigned short visited;
  unsigned short time;
} memo[1000];


unsigned short dfs(unsigned short v, unsigned short color) {
  if (memo[v].visited == color)
    return 0;
  
  memo[v].visited = color;
  memo[v].time = 0;
  
  for (unsigned short i = 0; i < 1000; i++) {
    if (graph[v][i] == -1)
      break;
    
    unsigned short deptime = dfs(graph[v][i], color);
    
    if (deptime == 0)
      return 0;
    
    memo[v].time = memo[v].time > deptime ? memo[v].time : deptime;
  }
  
  memo[v].time++;
  
  return memo[v].time;
}


int main() {
  while (scanf("%hu", &order) == 1) {
    memset(graph, -1, sizeof(graph));
    memset(memo, 0, sizeof(memo));
    
    for (unsigned short i = 0; i < order; i++) {
      unsigned short n;
      scanf("%hu", &n);
      
      for (unsigned short j = 0; j < n; j++) {
        unsigned short d;
        scanf("%hu", &d);
        graph[i][j] = d - 1;
      }
    }
    
    unsigned short max = 0;
    for (unsigned short i = 0; i < order; i++) {
      unsigned short time = memo[i].visited ? memo[i].time : dfs(i, i + 1);
      
      if (time == 0) {
        max = 0;
        break;
      }
      
      max = max > time ? max : time;
    }
    
    printf("%d\n", max == 0 ? -1 : (int) max);
  }
  
  return 0;
}
