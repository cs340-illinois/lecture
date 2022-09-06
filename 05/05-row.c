#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  unsigned int SIZE = 25000;
  if (argc == 2) { SIZE = atoi(argv[1]); }
  else           { printf("Using default SIZE=%d. Specify a specific size as a command line argument.\n", SIZE); }

  unsigned long allocationSizeMB = (SIZE * SIZE * sizeof(unsigned int)) / 1024 / 1024;
  printf("Allocation size: %ld MB\n", allocationSizeMB);

  // Allocate an array of SIZE x SIZE of `unsigned ints`:
  unsigned int *array = malloc(SIZE * SIZE * sizeof(unsigned int));

  // Add data to each element of the array:
  for (unsigned int c = 0; c < SIZE; c++) {
    for (unsigned int r = 0; r < SIZE; r++) {
      array[(r * SIZE) + c] = (r * SIZE) + c;
    }
  }

  return 0;
}
