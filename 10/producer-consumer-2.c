#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>

#define THINGS_MAX 10
#define THREAD_CT 5

int things[THINGS_MAX];
int things_ct = 0;




void print_things_as_list() {
  printf("[");
  for (int i = 0; i < things_ct; i++) {
    printf("%d", things[i]);
    if (i != things_ct - 1) { printf(", "); }
  }
  printf("]\n");
}


void *producer(void *vptr) {
  while (1) {
    // Cannot add to `things` if `things_ct` is len or larger:
    assert(things_ct < THINGS_MAX);

    // Produce a thing:
    things[things_ct] = rand() % 100;
    printf("Produced [%d]: %d -> ", things_ct, things[things_ct]);
    things_ct++;
    print_things_as_list();
  }
}

void *consumer(void *vptr) {
  while (1) {
    // Cannot consume from `things` if there's nothing in it
    assert(things_ct > 0);

    // Consume a thing:
    things_ct--;
    int value = things[things_ct];
    printf("Consumed [%d]: %d <- ", things_ct, value);
    print_things_as_list();
  }
}


int main() {
  int i;

  // Create `thread_ct` threads of each producer and consumer:
  pthread_t tid_consumer[THREAD_CT];
  pthread_t tid_producer[THREAD_CT];
  for (i = 0; i < THREAD_CT; i++) {
    pthread_create(&tid_consumer[i], NULL, producer, NULL);
    pthread_create(&tid_producer[i], NULL, consumer, NULL);
  }

  // Join threads:
  for (i = 0; i < THREAD_CT; i++) {
    pthread_join(tid_consumer[i], NULL);
    pthread_join(tid_producer[i], NULL);
  }
}