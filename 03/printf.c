#include <stdio.h>

int main() {
  int i = 42;
  char *s = "Hello, world!";
  float f = 3.14;

  printf("%d  %s  %f\n", i, s, f);
  printf("%d\n", s[0]);
  printf("%d\n", s);
  printf("%d\n", f);

  return 0;
}
