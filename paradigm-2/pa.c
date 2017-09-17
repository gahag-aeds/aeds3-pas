#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>


typedef struct {
  char name[20];
  short score;
} Student;

Student scan_student(void) {
  Student student = {
    { 0 },
    0
  };
  
  scanf("%15s", student.name);
  
  char* c;
  for (c = student.name; *c != '\0'; c++)
    student.score += *c;
  
  return student;
}


typedef struct {
  size_t size;
  Student* students;
} Class;

typedef struct {
  Student* pivot;
  long long score1, score2;
} Teams;

Teams make_teams(Class class, Student* pivot) {
  Teams ts = {
    .pivot = pivot,
    .score1 = 0,
    .score2 = 0
  };
  
  size_t i;
  size_t pivot_ix = pivot - class.students;
  
  for (i = 0; i <= pivot_ix; i++)
    ts.score1 += class.students[i].score * (pivot_ix - i + 1);
  
  for (i = pivot_ix + 1; i < class.size; i++)
    ts.score2 += class.students[i].score * (i - pivot_ix);
  
  return ts;
}

int compare_teams(Teams ts) {
  if (ts.score1 < ts.score2) return -1;
  if (ts.score1 > ts.score2) return 1;
  return 0;
}

Student* solve(Class class, Class subclass) {
  const size_t half = subclass.size / 2;
  Student* const pivot = &subclass.students[half];
  
  Teams teams = make_teams(class, pivot);
  
  const int cmp = compare_teams(teams);
  
  if (cmp == 0)
    return pivot;
  
  if (half == 0)
    return NULL;
  
  
  if (cmp > 0)
    return solve(
      class,
      (Class) {
        .size = half,
        .students = subclass.students
      }
    );
  
  return solve(
    class,
    (Class) {
      .size = subclass.size - half - 1,
      .students = subclass.students + half + 1
    }
  );
}


Student students[1000000];

int main() {
  while (true) {
    Class class = {
      .students = students
    };
    
    scanf("%zu", &class.size);
    
    if (class.size == 0)
      return 0;
    
    size_t i;
    for (i = 0; i < class.size; i++)
      class.students[i] = scan_student();
    
    Student* result = solve(class, class);
    
    puts(
      result != NULL ? result->name
                     : "Impossibilidade de empate."
    );
  }
  
  
  return 0;
}
