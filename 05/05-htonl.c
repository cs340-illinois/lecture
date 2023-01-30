#include <arpa/inet.h>
#include <stdio.h>

int main() {
  // By default, a variable is in "host order":
  uint32_t value = 66051;
  printf("value: 0x%08x; %%d == %d\n", value, value);

  // htonl coverts a "host order" value to "network order" (even if it might do nothing on some systems):
  uint32_t network_value = htonl(value);
  printf("htonl: 0x%08x; %%d == %d\n", network_value, network_value);

  // ntohl converts a "network order" value to "host order" (even if it might do nothing on some systems):
  uint32_t host_value = ntohl(network_value);
  printf("ntohl: 0x%08x; %%d == %d\n", host_value, host_value);
}