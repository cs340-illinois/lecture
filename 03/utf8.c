#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  char *s = malloc(5);
  s[0] = 0xF0; s[1] = 0x9F; s[2] = 0x8E; s[3] = 0x89; s[4] = 0x00;

  char *s1 = "\xF0\x9F\x8E\x89";
  char *s2 = "🎉";
  char *s3 = "\U0001f389";    // \U - must be 8 bytes

  printf("%s %s %s %s\n", s, s1, s2, s3);
  printf("strlen(): %ld %ld %ld %ld\n", strlen(s), strlen(s1), strlen(s2), strlen(s3));
  return 0;
}