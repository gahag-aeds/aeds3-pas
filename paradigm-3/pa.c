#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
  size_t start, duration;
} Task;

int compare_tasks(const void* _t1, const void* _t2) {
  Task t1 = *(const Task*) _t1;
  Task t2 = *(const Task*) _t2;

  if (t1.start < t2.start) return -1;
  if (t1.start > t2.start) return 1;
  return 0;
}


Task tasks[100000];

int main() {
  while (true) {
    size_t i;
    
    size_t tasks_count;
    size_t time = 1;
    
    if (scanf("%zu", &tasks_count) != 1)
      return 0;
    
    
    for (i = 0; i < tasks_count; i++)
      scanf("%zu %zu", &tasks[i].start, &tasks[i].duration);
    
    
    qsort(tasks, tasks_count, sizeof(Task), compare_tasks);
    
    
    for (i = 0; i < tasks_count; i++) {
      if (tasks[i].start > time)
        time += tasks[i].start - time;
      
      time += tasks[i].duration;
    }
    
    
    printf("%zu\n", time);
  }
}
