#include <stdlib.h>
#include <stdio.h>

int main() {
  char *s = malloc(10);
  int *num = malloc( sizeof(int) );
  
  printf("%p %p\n", s, num);
  return 0;
}