#include <stdio.h>
#include <stdlib.h>

int main() {
  int val;
  printf(" &val: %p\n", &val);

  int *ptr = malloc(0x1000);
  printf(" &ptr: %p\n", &ptr);
  printf("  ptr: %p\n", ptr);

  int *ptr2 = malloc(0x1000);
  printf("&ptr2: %p\n", &ptr2);
  printf(" ptr2: %p\n", ptr2);

  int arr[4096];
  printf(" &arr: %p\n", &arr);

  return 0;
}