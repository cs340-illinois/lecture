#include <stdio.h>
#include <stdlib.h>

int main() {
  int *a = malloc(4096);
  printf("a = %p\n", a);
  free(a);
  
  int *b = malloc(4096);
  printf("b = %p\n", b);

  int *c = malloc(4096);
  printf("c = %p\n", c);
  
  int *d = malloc(4096);
  printf("d = %p\n", d);

  free(b);
  free(c);

  int *e = malloc(5000);
  printf("e = %p\n", e);

  int *f = malloc(10);
  printf("f = %p\n", f);

  int *g = malloc(10);
  printf("g = %p\n", g);

  return 0;
}