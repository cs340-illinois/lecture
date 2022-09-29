#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>

int main() {
  // socket:
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  // bind:
  struct sockaddr_in server_addr, client_address;
  memset(&server_addr, 0x00, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(24000);  
  bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr));

  // listen:
  listen(sockfd, 10);

  // accept:
  int client_addr_len;
  int fd = accept(sockfd, (struct sockaddr *)&client_address, &client_addr_len);

  while (1) {
    char buffer[4096];
    ssize_t len = read(fd, buffer, 4096);
    buffer[len] = '\0';
    printf("== read() %ld bytes ==\n", len);
    printf("%s\n", buffer);
  }

  return 0;
}
