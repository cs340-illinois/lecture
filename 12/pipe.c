#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parent(int pipe_read_fd) {
  char *buffer = malloc(100);
  ssize_t len = read(pipe_read_fd, buffer, 100);
  buffer[len] = '\0';

  printf("Message: %s\n", buffer);
}

void child(int pipe_write_fd) {
  const char *s = "Hello world!";
  write(pipe_write_fd, s, strlen(s));
}


int main() {
  int pipefd[2];
  pipe(pipefd);

  pid_t pid = fork();
  printf("fork()=%d, mypid=%d\n", pid, getpid());
  if (pid < 0) {
    // Failed:
    perror("Fork failed!");
  } else if (pid == 0) {
    // Child:
    child(pipefd[1]);
  } else {
    // Parent:
    parent(pipefd[0]);
  }
  printf("%d exiting\n", getpid());

  return 0;
}
