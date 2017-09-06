#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  char id[30];
  unsigned short points;
  short goals_difference;
} Team;


int main() {
  size_t test_id = 0;
  
  while (true) {
    unsigned short teams_count;
    size_t total_games, completed_games;
    
    scanf("%hud", &teams_count);
    
    if (teams_count == 0)
      return 0;
    
    total_games = teams_count * teams_count - teams_count;
    
    scanf("%zu", &completed_games);
    
    for (size_t i = 0; i < completed_games; i++) {
      
    }
    
    printf("Group #%zu\n", test_id);
    test_id++;
  }
  
  
  return 0;
}
