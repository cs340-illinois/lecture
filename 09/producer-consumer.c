#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define THINGS_MAX 10
#define THREAD_CT 5

pthread_mutex_t lock;
pthread_cond_t cond;

int things[THINGS_MAX];
int things_ct = 0;

void *producer(void *vptr) {
  while (1) {
    pthread_mutex_lock(&lock);

    // Cannot produce until there's space:
    while (things_ct >= THINGS_MAX) {
      pthread_cond_wait(&cond, &lock);
    }

    // Produce a thing:
    things[things_ct] = rand();
    printf("Produced [%d]: %d\n", things_ct, things[things_ct]);
    things_ct++;

    // Signal any waiting consumers:
    pthread_cond_broadcast(&cond);

    pthread_mutex_unlock(&lock);
  }
}

void *consumer(void *vptr) {
  while (1) {
    pthread_mutex_lock(&lock);

    // Cannot consume a thing until one exists:
    while (things_ct == 0) {
      pthread_cond_wait(&cond, &lock);
    }

    // Consume a thing:
    things_ct--;
    int value = things[things_ct];
    printf("Consumed [%d]: %d\n", things_ct, value);

    // Signal any waiting producers:
    pthread_cond_broadcast(&cond);

    pthread_mutex_unlock(&lock);
  }
}


int main() {
  int i;

  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&cond, NULL);

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