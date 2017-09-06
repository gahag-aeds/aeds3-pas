#include <stdio.h>

#define ever ;;


int main() {
  unsigned short size;
  
  for (ever) {
    unsigned short i;
    char str[100] = "                                                                                                   ";
    
    scanf("%hu", &size);
    
    if (feof(stdin))
      return 0;
    
    const unsigned short pivot = (size - 1) / 2;
    
    str[pivot] = '*';
    str[pivot + 1] = '\0';
    puts(str);
    
    for (i = 1; i <= pivot; i++) {
      str[pivot - i] =
      str[pivot + i] = '*';
      str[pivot + i + 1] = '\0';
      
      puts(str);
    }
    
    for (i = 0; i < pivot; i++)
        putchar(' ');
    puts("*");
    
    for (i = 1; i < pivot; i++)
        putchar(' ');
    puts("***\n");
  }
}
