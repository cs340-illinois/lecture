#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>


void *client_communication_thread(void *vptr_fd) {
  int fd = *((int *)vptr_fd);
  char buffer[4096];

  while (1) {
    // recv message:
    ssize_t len = recv(fd, buffer, 4096, 0);
    if (len == -1) {
      printf("[%d]: socket closed\n", fd);
      break;
    } else if (len == 0) { 
      continue;
    }
    buffer[len] = '\0';

    printf("[%d]:   recv(): ", fd);
    for (int i = 0; i < len; i++) {
      printf("%02x ", buffer[i]);
    }
    printf("\n");
    printf("[%d]:   recv(): %s\n", fd, buffer);

    // send response:
    sprintf(buffer, "Your %ld bytes were received, thank you for sending them!\n", len);
    send(fd, buffer, strlen(buffer), 0);
  }

  return NULL;
}

int main() {
  const int PORT = 34000;

  // socket:
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd <= 0) { perror("socket"); return 1; }
  printf("socket: returned fd=%d\n", sockfd);

  // bind:
  struct sockaddr_in server_addr;
  memset(&server_addr, 0x00, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);  
  if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
    perror("bind");
    return 1;
  }
  printf("bind: binding fd=%d to port %d (:%d)\n", sockfd, PORT, PORT);

  // listen:
  if (listen(sockfd, 10) != 0) {
    perror("listen");
    return 1;
  }
  printf("listen: fd=%d is now listening for incoming connections\n", sockfd);

  // continue to accept new connections forever:
  while (1) {
    struct sockaddr_in client_address;
    socklen_t client_addr_len = sizeof(struct sockaddr_in);

    // accept:
    int *fd = malloc(sizeof(int));
    *fd = accept(sockfd, (struct sockaddr *)&client_address, &client_addr_len);
    
    char *ip = inet_ntoa(client_address.sin_addr);
    printf("accept: new client connected from %s, communication on fd=%d\n", ip, *fd);

    pthread_t tid;
    pthread_create(&tid, NULL, client_communication_thread, fd);
  }

  return 0;
}
