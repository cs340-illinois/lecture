#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>


// Private Globals:
pthread_mutex_t __lock;
int __in_cs = 0;
int __ct = 0;
pthread_t __tid_barber;


void ERROR(const char *s) {
  fprintf(stderr, "ERROR: %s\n", s);
  exit(1);
}

void cut_hair(const char *name) {
  if (name == NULL) {
    ERROR("You cannot cut the hair of a NULL pointer.");
  }
    
  if (strcmp(name, "waf") == 0) {
    ERROR("There is no customer named `waf` who wants a hair cut right now.");
  }

  if (pthread_self() != __tid_barber) {
    ERROR("The barber must be the thread cutting the hair (you can't cut your own hair).");
  }

  pthread_mutex_lock(&__lock);
  if (__in_cs) { ERROR("Two customers are getting their hair cut at once!"); }
  __in_cs = 1;
  printf("%s is getting their hair cut...\n", name);
  pthread_mutex_unlock(&__lock);

  usleep(100);

  pthread_mutex_lock(&__lock);
  printf("%s is leaving with a new hair cut. It looks great!\n", name);
  __in_cs = 0;
  __ct++;

  pthread_mutex_unlock(&__lock);
}


// Library Code:
#include "sleeping-barber.c"


// Runner:
sleeping_barber_t sb;

void *__barber(void *vptr) {
  barber(&sb);
}

void *__customer(void *vptr_name) {
  const char *name = (const char *)vptr_name;
  if (name != NULL) {
    printf("%s arrived to get their hair cut.\n", name);
  } else {
    printf("All customers have had their hair cut.  Sending `NULL` customer to exit barber.\n");
  }

  customer(&sb, (const char *)vptr_name);
}

void *__timer(void *vptr) {
  sleep(5);
  ERROR("Timeout.  It looks like you have deadlocked or your barber did not exit.");
}


int main(int argc, char *argv[])  {
  pthread_mutex_init(&__lock, NULL);
  init(&sb);

  // Timer Monitor:
  pthread_t tid_timer;
  pthread_create(&tid_timer, NULL, __timer, NULL);

  pthread_create(&__tid_barber, NULL, __barber, NULL);

  // Workers:
  pthread_t tid[7];
  pthread_create(&tid[0], NULL, __customer, "Anna");
  pthread_create(&tid[1], NULL, __customer, "Ameya");
  pthread_create(&tid[2], NULL, __customer, "Jackson");
  pthread_create(&tid[3], NULL, __customer, "Jeremy");
  sleep(2);
  pthread_create(&tid[4], NULL, __customer, "Sana");
  pthread_create(&tid[5], NULL, __customer, "Aarya");
  pthread_create(&tid[6], NULL, __customer, "Effie");

  for (int i = 0; i < 7; i++) {
    pthread_join(tid[i], NULL);
  }

  // NULL
  pthread_t tid_exit;
  pthread_create(&tid_exit, NULL, __customer, NULL);
  
  pthread_join(__tid_barber, NULL);

  if (__ct != 7) {
    ERROR("Not every has had their hair cut! :(");
  }

  printf("Customers: %d\n", __ct);
}
