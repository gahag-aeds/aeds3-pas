#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef char Name[30];

typedef struct {
  Name name;
  
  unsigned short points;
  short goals_scored;
  short goals_difference;
} Team;

typedef struct {
  size_t size;
  Team* teams;
} Group;


typedef struct {
  // Team* t1;
  // Team* t2;
  
  bool played;
} Game;

typedef struct {
  size_t games_count;
  Game* games;
  
  Group group;
} EuroCup;


int team_lexicographic(const void* _t1, const void* _t2) {
  const Team* t1 = _t1;
  const Team* t2 = _t2;
  
  return strcmp(t1->name, t2->name);
}

Game* get_game(EuroCup cup, Team* t1, Team* t2) {
  assert(t1 != NULL && t2 != NULL);
  
  signed int t1_ix = t1 - cup.group.teams;
  signed int t2_ix = t2 - cup.group.teams;
  
  if (t1_ix > t2_ix) {
    signed int aux = t1_ix;
    t1_ix = t2_ix;
    t2_ix = aux;
  }
  
  signed int size = cup.group.size;
  size_t game_ix = 2*(t2_ix - t1_ix - 1) - t1_ix*(t1_ix - 2*size + 1);
  
  assert(0 <= game_ix && game_ix < cup.games_count);
  
  return &cup.games[game_ix];
}

Team* get_team(Group group, Name name) {
  const size_t half = group.size / 2;
  Team* const pivot = &group.teams[half];
  
  const int cmp = strcmp(pivot->name, name);
  
  if (cmp == 0)
    return pivot;
  
  if (half == 0) {
    return NULL;
  }
  
  if (cmp > 0)
    return get_team(
      (Group) {
        .size = half,
        .teams = group.teams
      },
      name
    );
  
  return get_team(
    (Group) {
      .size = group.size - half - 1,
      .teams = group.teams + half + 1
    },
    name
  );
}

short match_balance(short g1, short g2) {
  return g1 < g2  ? 0
       : g1 == g2 ? 1
       : 3;
}



int main() {
  size_t test_id = 0;
  
  while (true) {
    EuroCup cup;
    size_t completed_games;
    
    
    scanf("%zu", &cup.group.size);
    
    if (cup.group.size == 0)
      return 0;
    
    
    cup.group.teams = malloc(cup.group.size * sizeof(Team));
    
    cup.games_count = cup.group.size * cup.group.size - cup.group.size;
    cup.games = malloc(cup.games_count * sizeof(Game));
    
    
    for (size_t i = 0; i < cup.group.size; i++) {
      scanf("%29s", cup.group.teams[i].name);
      cup.group.teams[i].points = 0;
      cup.group.teams[i].goals_scored = 0;
      cup.group.teams[i].goals_difference = 0;
    }
    
    qsort(cup.group.teams, cup.group.size, sizeof(Team), team_lexicographic);
    
    
    scanf("%zu", &completed_games);
    
    for (size_t i = 0; i < completed_games; i++) {
      Name name;
      Team* t1;
      Team* t2;
      short goals_t1, goals_t2;
      
      scanf("%29s", name);
      t1 = get_team(cup.group, name);
      
      scanf("%29s", name);
      t2 = get_team(cup.group, name);
      
      scanf("%hd %hd", &goals_t1, &goals_t2);
      
      get_game(cup, t1, t2)->played = true;
      
      t1->goals_scored += goals_t1;
      t1->goals_difference += goals_t1 - goals_t2;
      t1->points += match_balance(goals_t1, goals_t2);
      
      t2->goals_scored += goals_t2;
      t2->goals_difference += goals_t2 - goals_t1;
      t2->points += match_balance(goals_t2, goals_t1);
    }
    
    
    printf("Group #%zu\n", test_id);
    for (size_t i = 0; i < cup.group.size; i++) {
      Team* team = &cup.group.teams[i];
      printf("%s %hd %hd %hd\n", team->name, team->points, team->goals_scored, team->goals_difference);
    }
    test_id++;
    
    
    free(cup.group.teams);
    free(cup.games);
  }
  
  
  return 0;
}
