#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
 
const int num_threads = 15;
 
void *thread_start(void *ptr) {
  int id = *((int *)ptr);
  printf("Thread %d running...\n", id);
  return NULL;
}
 
int main(int argc, char *argv[]) {
  // Create threads:
  int i;
  pthread_t tid[num_threads];
  for (i = 0; i < num_threads; i++) {
    int *val = malloc(sizeof(int));
    *val = i;
    pthread_create(&tid[i], NULL, thread_start, (void *)val);
  }
 
  // Joining Threads
  for (i = 0; i < num_threads; i++) {
    pthread_join(tid[i], NULL);
  }
 
  printf("Done!\n");
  return 0;
}
