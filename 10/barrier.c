#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>


typedef pthread_t * promise_t;

void *idle_task(void *vptr) {
  printf("idle_task is running.\n");
  sleep(5);
  printf("idle_task has finished.\n");
  return NULL;
}

promise_t async_task(void*(* task)(void *), void *arg) {
  pthread_t *tidptr = malloc(sizeof(pthread_t));
  pthread_create(tidptr, NULL, task, arg);
  return tidptr;
}

void *async_wait(promise_t promise) {
  void *result;
  pthread_join(*promise, &result);
  return result;
}

int main() {
  promise_t p = async_task(idle_task, NULL);
  printf("main thread is running at the same time...\n");
  async_wait(p);
  printf("main thread has running again...\n");
  return 0;
}