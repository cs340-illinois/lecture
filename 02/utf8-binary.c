#include <stdio.h>

int main() {
  unsigned char message[] = {
    0b01001000, 0b01101001, 0b11110000, 0b10011111, 0b10001110, 0b10001001, 0
  };
  printf("%s\n", message);

  return 0;
}