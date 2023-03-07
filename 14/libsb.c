#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>

struct _sleeping_barber_t {
  // Add any variables here; initialize them in `init`:
  
};

typedef struct _sleeping_barber_t sleeping_barber_t;


void init(sleeping_barber_t *sb) {

}

void barber(sleeping_barber_t *sb) {
  // The barber must continue to run until a customer with `name == NULL` arrives.
  // ...you should NOT remove this while(1) statement.
  while (1) {  
    cut_hair("waf");
  }
}

void customer(sleeping_barber_t *sb, const char *name) {
  // Each customer is a thread! :)
}