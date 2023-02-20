#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>

void job(char *ptr, char start_letter) {
  char buffer[2];
  buffer[0] = start_letter;
  buffer[1] = '\0';

  for (int i = 0; i < 26; i++) {
    usleep(10);
    strcat(ptr, buffer);
    buffer[0]++;

    printf("%s\n", ptr);
  }
}

void parent(char *ptr) {
  job(ptr, 'A');
}

void child(char *ptr) {
  job(ptr, 'a');
}


int main() {
  int pipefd[2];
  pipe(pipefd);

  //char *ptr = malloc(100);
  char *ptr = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);

  printf("%p\n", ptr);
  ptr[0] = '\0';
  
  pid_t pid = fork();
  printf("fork()=%d, mypid=%d\n", pid, getpid());
  if (pid < 0) {
    // Failed:
    perror("Fork failed!");
  } else if (pid == 0) {
    // Child:
    child(ptr);
  } else {
    // Parent:
    parent(ptr);
  }
  printf("%d exiting\n", getpid());

  return 0;
}
