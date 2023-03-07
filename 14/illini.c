#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include "illini-main.h"

// The `init` function will be called exactly once,
// and will be called before any other function:
void init() {
  
}


// When the `cheer` function is called, you must synchronize the
// threads to shout `I L L I N I` in exactly that order:
void cheer() {

}


// All threads calling the `thread_I` function can only shout the letter 'I'.
// You must synchronize access to the `shout` function among all of your threads.
void thread_I() {
  while (1) {
    shout('I');
  }
}

// All threads calling the `thread_L` function can only shout the letter 'L'.
// You must synchronize access to the `shout` function among all of your threads.
void thread_L() {
  while (1) {
    shout('L');
  }
}

// All threads calling the `thread_N` function can only shout the letter 'N'.
// You must synchronize access to the `shout` function among all of your threads.
void thread_N() {
  while (1) {
    shout('N');
  }
}