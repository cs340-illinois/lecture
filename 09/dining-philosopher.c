#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define PHILOSOPHER_COUNT 5

pthread_mutex_t locks[PHILOSOPHER_COUNT];
int ct = 0;

void *philosopher_thread(void *ptr) {
  int id = *((int *)ptr);

  int left_chopstick_id = id;
  int right_chopstick_id = (id + 1) % PHILOSOPHER_COUNT;

  while (1) {
    printf("%d is thinking...\n", id);
 
    // Get left chopstick:
    printf("%d is reaching for the left chopstick (chopstick=%d)...\n", id, left_chopstick_id);
    pthread_mutex_lock(&locks[left_chopstick_id]);    
    printf("%d has the left chopstick (chopstick=%d).\n", id, left_chopstick_id);
 
    // Get right chopstick:
    printf("%d is reaching for the right chopstick (chopstick=%d)...\n", id, right_chopstick_id);
    pthread_mutex_lock(&locks[right_chopstick_id]);    
    printf("%d has the right chopstick (chopstick=%d).\n", id, right_chopstick_id);
 
    // Eat:
    printf("%d is eating... 🍱🥢\n", id);
 
    // Release chopsticks:
    printf("%d is returning their chopsticks  (chopsticks: %d, %d)...\n", id, left_chopstick_id, right_chopstick_id);
    pthread_mutex_unlock(&locks[right_chopstick_id]);    
    pthread_mutex_unlock(&locks[left_chopstick_id]);    
  }

  return NULL;
}

int main(int argc, char *argv[]) {
  int i;

  // Create locks (one for each chopstick):
  for (i = 0; i < PHILOSOPHER_COUNT; i++) {
    pthread_mutex_init(&locks[i], NULL);
  }

  // Create threads:
  pthread_t tid[PHILOSOPHER_COUNT];
  for (i = 0; i < PHILOSOPHER_COUNT; i++) {
    int *id = malloc(sizeof(int));
    *id = i;
    pthread_create(&tid[i], NULL, philosopher_thread, (void *)id);
  }

  // Join threads:
  for (i = 0; i < PHILOSOPHER_COUNT; i++) {
    pthread_join(tid[i], NULL);
  }

  // Clean Up Lock:
  for (i = 0; i < PHILOSOPHER_COUNT; i++) {
    pthread_mutex_destroy(&locks[i]);
  }

  // Display result:
  printf("Final Result: %d\n", ct);
}
