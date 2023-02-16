#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include "sleeping-barber.h"

struct _sleeping_barber_t {
  pthread_mutex_t *lock;
  pthread_cond_t *cond;
  int customers;
  const char *customer_name;
};
typedef struct _sleeping_barber_t sleeping_barber_t;

void init(sleeping_barber_t *sb) {
  sb->lock = malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(sb->lock, NULL);

  sb->cond = malloc(sizeof(pthread_cond_t));
  pthread_cond_init(sb->cond, NULL);

  sb->customers = 0;
}

void barber(sleeping_barber_t *sb) {
  while (1) {  
    pthread_mutex_lock(sb->lock);

    // Sleep while there's no customers:
    while (sb->customers == 0) {
      pthread_cond_wait(sb->cond, sb->lock);
    }

    // Exit on NULL customer:
    if (sb->customer_name == NULL) { break; }

    // Otherwise, cut hair and then advance to the next customer:
    cut_hair(sb->customer_name);
    sb->customers--;
    pthread_cond_broadcast(sb->cond);

    pthread_mutex_unlock(sb->lock);
  }
}

void customer(sleeping_barber_t *sb, const char *name) {
  // Each customer is a thread! :)
  pthread_mutex_lock(sb->lock);

  // Block while there are other customers:
  while (sb->customers > 0) {
    pthread_cond_wait(sb->cond, sb->lock);
  }

  // The current customer takes the seat and notifies the barber:
  sb->customer_name = name;
  sb->customers++;
  pthread_cond_broadcast(sb->cond);

  pthread_mutex_unlock(sb->lock);  
}