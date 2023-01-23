#include <stdlib.h>
#include <stdio.h>

typedef struct _myObject {
  int value;
  char *s;
} myObject;

int main() {
  char *s = malloc(10);
  myObject *obj = malloc( sizeof(myObject) );
  obj->value = 3;
  
  printf("%p %p %d\n", s, obj, obj->value);
  return 0;
}