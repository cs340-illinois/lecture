#include <stdio.h>

int main() {
  int i = 3 + (2 << 8) + (1 << 16);
  char *s = (char *)&i;
  printf("%02x %02x %02x %02x\n",
            s[0], s[1], s[2], s[3]);
  return 0;
}