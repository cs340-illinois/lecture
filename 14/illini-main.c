#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

// Private Globals:
pthread_mutex_t __lock;
int __ct = 0;
int __successful = 0;
int __in_cs = 0;
pthread_t __tid_i[10], __tid_l[10], __tid_n[10];
int usage_i[10], usage_l[10], usage_n[10];
int __started = 0;

void ERROR(const char *s) {
  fprintf(stderr, "\n\nERROR: %s\n", s);
  exit(1);
}

void shout(char letter) {
  if (!__started) {
    ERROR("The `cheer` function has not been called.  No shouting until we're told to cheer! :(");
  }

  // Track entry into the critical section:
  pthread_mutex_lock(&__lock);
  if (__in_cs == 1) {
    ERROR("Only one thread may shout at any given time.");
  }
  __in_cs = 1;
  pthread_mutex_unlock(&__lock);


  // Print the shout out to console:
  fprintf(stderr, "%c", letter);


  // Verify correctness of the program:
  pthread_mutex_lock(&__lock);
  // Verify correct letter in sequence:
  char *s = NULL;
  if (__ct == 0 && letter != 'I') { asprintf(&s, "The first letter of the cheer must be an I.  You shouted a %c.\n", letter); }
  if (__ct == 1 && letter != 'L') { asprintf(&s, "The second letter of the cheer must be an L.  You shouted a %c.\n", letter); }
  if (__ct == 2 && letter != 'L') { asprintf(&s, "The third letter of the cheer must be an L.  You shouted a %c.\n", letter); }
  if (__ct == 3 && letter != 'I') { asprintf(&s, "The fourth letter of the cheer must be an I.  You shouted a %c.\n", letter); }
  if (__ct == 4 && letter != 'N') { asprintf(&s, "The fifth letter of the cheer must be an N.  You shouted a %c.\n", letter); }
  if (__ct == 5 && letter != 'I') { asprintf(&s, "The sixth letter of the cheer must be an I.  You shouted a %c.\n", letter); }
  if (s != NULL) { ERROR(s); }

  // Verify correct thread:
  int found = 0;
  pthread_t self = pthread_self();
  for (int i = 0; i < 10; i++) {
    if (letter == 'I' && self == __tid_i[i]) { usage_i[i]++; found = 1; break; }
    if (letter == 'L' && self == __tid_l[i]) { usage_l[i]++; found = 1; break; }
    if (letter == 'N' && self == __tid_n[i]) { usage_n[i]++; found = 1; break; }
  }

  if (!found) {
    char *s = NULL;
    asprintf(&s, "The letter %c must be shouted fro a `thread_%c` thread.\n", letter, letter);
    ERROR(s);
  }
  
  // Count successful runs:
  __ct++;
  if (__ct == 6) {
    __successful++;
    fprintf(stderr, "\n");
  } else {
    fprintf(stderr, " - ");
  }
  pthread_mutex_unlock(&__lock);


  // Track exit of critical section:
  pthread_mutex_lock(&__lock);
  if (__in_cs == 0) {
    ERROR("Only one thread may shout at any given time.");
  }  
  __in_cs = 0;
  pthread_mutex_unlock(&__lock);
}


// Library Code:
#include "illini.c"


// Threads:
void *__timer(void *vptr) {
  sleep(5);
  ERROR("Timeout.  It looks like you have deadlocked.");
}

void *__thread_I(void *vptr) {
  thread_I();
}

void *__thread_L(void *vptr) {
  thread_L();
}

void *__thread_N(void *vptr) {
  thread_N();
}

void *__cheer(void *vptr) {
  __ct = 0;
  cheer();
}

int main(int argc, char *argv[])  {
  pthread_t tid_cheer;
  pthread_mutex_init(&__lock, NULL);
  init();

  // Counting thread usage:
  for (int i = 0; i < 10; i++) {
    usage_i[i] = 0;
    usage_l[i] = 0;
    usage_n[i] = 0;
  }

  // Timer Monitor:
  pthread_t tid_timer;
  pthread_create(&tid_timer, NULL, __timer, NULL);

  // Worker Threads:
  pthread_create(&__tid_i[0], NULL, __thread_I, NULL);
  pthread_create(&__tid_l[0], NULL, __thread_L, NULL);
  pthread_create(&__tid_n[0], NULL, __thread_N, NULL);
  usleep(100);
  __started = 1;

  // == One Thread Test ==
  printf("Testing Cheer w/ One Thread /Letter:\n");
  pthread_create(&tid_cheer, NULL, __cheer, NULL);
  pthread_join(tid_cheer, NULL);
  if (__ct != 6) { ERROR("The `cheer` function must not return until the cheer is complete."); }

  // == Ten Thread Test ==
  for (int i = 1; i < 10; i++) {
    pthread_create(&__tid_i[i], NULL, __thread_I, NULL);
    pthread_create(&__tid_l[i], NULL, __thread_L, NULL);
    pthread_create(&__tid_n[i], NULL, __thread_N, NULL);
  }

  fprintf(stderr, "Testing Cheer w/ Many Threads /Letter:\n");
  pthread_create(&tid_cheer, NULL, __cheer, NULL);
  pthread_join(tid_cheer, NULL);
  if (__ct != 6) { ERROR("The `cheer` function must not return until the cheer is complete."); }

  // == 10x Test ==
  fprintf(stderr, "Testing Cheer 10 more times:\n");
  for (int i = 0; i < 10; i++) {
    pthread_create(&tid_cheer, NULL, __cheer, NULL);
    pthread_join(tid_cheer, NULL);
    if (__ct != 6) { ERROR("The `cheer` function must not return until the cheer is complete."); }
  }

  // Verify Correctness:
  if (__successful != 12) {
    ERROR("You did not cheer 12 times! :(");
  }

  fprintf(stderr, "Thread Usage: ");
  for (int i = 0; i < 10; i++) {
    fprintf(stderr, "(%d,%d,%d) ", usage_i[i], usage_l[i], usage_n[i]);
  }
  fprintf(stderr, "\n");

  int total_i = 0, total_l = 0, total_n = 0;
  for (int i = 1; i < 10; i++) {
    total_i += usage_i[i];
    total_l += usage_l[i];
    total_n += usage_n[i];
  }

  if (total_i == 0) {
    ERROR("Each thread must have an equal chance of giving a cheer.  (All your cheers for a given letter were on one thread.)");
  }
  if (total_l == 0) {
    ERROR("Each thread must have an equal chance of giving a cheer.  (All your cheers for a given letter were on one thread.)");
  }
  if (total_n == 0) {
    ERROR("Each thread must have an equal chance of giving a cheer.  (All your cheers for a given letter were on one thread.)");
  }

  printf("Cheers Completed: %d\n", __successful);
}