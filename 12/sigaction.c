#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

void handle_SIGINT(int signum) {
  printf("Can't Ctrl+C me!\n");
}



int main() {
  struct sigaction action;
  action.sa_handler = handle_SIGINT;
  action.sa_flags = 0;
  sigaction(SIGINT, &action, NULL);

  while (1) {
    sleep(1);
  }
  return 0;
}
