#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int ct = 0;
 
void *thread_start(void *ptr) {
  int countTo = *((int *)ptr);
 
  int i;
  for (i = 0; i < countTo; i++) {
    ct = ct + 1;
  }
 
  return NULL;
}
 
int main(int argc, char *argv[]) {
  // Parse Command Line:
  if (argc != 3)  {
    printf("Usage: %s <countTo> <thread count>\n", argv[0]);
    return 1;
  }
 
  const int countTo = atoi(argv[1]);
  if (countTo == 0) { printf("Valid `countTo` is required.\n"); return 1; }
 
  const int thread_ct = atoi(argv[2]);
  if (thread_ct == 0) { printf("Valid thread count is required.\n"); return 1; }

  // Create threads:
  int i;
  pthread_t tid[thread_ct];
  for (i = 0; i < thread_ct; i++) {
    pthread_create(&tid[i], NULL,
                         thread_start, (void *)&countTo);
  }
 
  // Join threads:
  for (i = 0; i < thread_ct; i++) {
    pthread_join(tid[i], NULL);
  }
 
  // Display result:
  printf("Final Result: %d\n", ct);
  return 0;
}
