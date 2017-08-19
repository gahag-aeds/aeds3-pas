#include <stdio.h>

#define ever ;;


int main() {
  unsigned short size;
  
  for (ever) {
    scanf("%hu", &size);
    
    if (feof(stdin))
      return 0;
    
    for (unsigned short i = size - 2; i > 0; i--) {
      for (unsigned short j = i / 2; j > 0; j--)
        putchar(' ');
      puts("*");
    }
    
    puts(" *");
    puts("***");
  }
}
