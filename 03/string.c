#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {  
  char *s = malloc(6);
  strcpy(s, "cs340");
  printf("s[0]: 0x%x == %d == %c\n", s[0], s[0], s[0]);
  printf("s[4]: 0x%x == %d == %c\n", s[4], s[4], s[4]);
  printf("s[5]: 0x%x == %d == %c\n", s[5], s[5], s[5]);
  printf("s == \"%s\", strlen(s): %ld\n\n", s, strlen(s));

  char *s2 = s + 2;
  printf("s2[0]: 0x%x == %d == %c\n", s2[0], s2[0], s2[0]);
  printf("s2 == \"%s\", strlen(s2): %ld\n\n", s2, strlen(s2));

  *s2 = 0;
  printf("s2[0]: 0x%x == %d == %c\n", s2[0], s2[0], s2[0]);
  printf("s2 == \"%s\", strlen(s2): %ld\n\n", s2, strlen(s2));

  printf("s == \"%s\", strlen(s): %ld\n", s, strlen(s));
  return 0;
}